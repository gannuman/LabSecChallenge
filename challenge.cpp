#include <iostream>
#include <fstream>
#include <list>
#include <stdio.h>
#include <libcryptosec/MessageDigest.h>
#include <libcryptosec/ByteArray.h>
#include <libcryptosec/Signer.h>
#include <libcryptosec/KeyPair.h>
#include <libcryptosec/AsymmetricKey.h>
using namespace std;

typedef struct {
	ByteArray* digest;
	list<PublicKey*> pkeys;
	list<ByteArray*> signatures;
} MultiSign;

int main(int argc, char **argv) {
	
	// Confere o input do programa
	if (argc != 2) {
		std::cerr << "Usage: cryp FILE " << std::endl; 

		return 1;
	}

	// Carrega o arquivo inputado;
	streampos size;
	char * memblock;
	
	ifstream file (argv[1], ios::in | ios::ate | ios::binary);
	if (file.is_open()) {
		size = file.tellg();
		memblock = new char [size];
		file.seekg (0, ios::beg);
		file.read (memblock, size);
		file.close();
		cout << "File opened." << endl;
	} else cout << "File could not be opened." << endl;

	ByteArray undigested (memblock);

	// Digere o input
	MessageDigest::loadMessageDigestAlgorithms();

	MessageDigest digest (MessageDigest::SHA512);
	ByteArray digested = digest.doFinal(undigested);

	cout << digested.toString() << endl;

	MultiSign ms; ms.digest = &digested;

	// Gera par de chaves
	KeyPair keys1 (AsymmetricKey::RSA, 2048);
	ms.pkeys.push_front(keys1.getPublicKey());
	KeyPair keys2 (AsymmetricKey::RSA, 2048);
	ms.pkeys.push_front(keys2.getPublicKey());
	KeyPair keys3 (AsymmetricKey::RSA, 2048);
	ms.pkeys.push_front(keys3.getPublicKey());

	// Assina o input digerido
	ByteArray assinado1 = Signer::sign(*keys1.getPrivateKey(), digested, MessageDigest::SHA512);
	ms.signatures.push_front(&assinado1);
	ByteArray assinado2 = Signer::sign(*keys2.getPrivateKey(), digested, MessageDigest::SHA512);
	ms.signatures.push_front(&assinado2);
	ByteArray assinado3 = Signer::sign(*keys3.getPrivateKey(), digested, MessageDigest::SHA512);
	ms.signatures.push_front(&assinado3);

	// Verifica a assinatura
	int verified_count = 0;
	bool verified_flag = false;
	for (list<PublicKey*>::iterator pk = ms.pkeys.begin(); pk != ms.pkeys.end(); ++pk) {
		 for (list<ByteArray*>::iterator signd = ms.signatures.begin(); signd != ms.signatures.end(); ++signd) {
		 	if (Signer::verify(**pk, **signd,*ms.digest, MessageDigest::SHA512)) {
				cout << "verified " << verified_count << endl;
				verified_flag = true;
				break;
			}

		 }
		 if (!verified_flag) {
			cout << "Signature " << verified_count << " not verified." << endl;
			break;
		} else {
			verified_count++;
			verified_flag = false;
		}
	}
	
	return 0;
}

