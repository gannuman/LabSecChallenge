#include "user.h"

User::User(std::string common_name) {
	RDNSequence rdnseq = new RDNSequence();
	rdnseq.addEntry(RDNSequence::COMMON_NAME, common_name);
	
	RSAKeyPair keys = RSAKeyPair(2048);
	privkey = keys.getPrivateKey();
	publkey = keys.getPublicKey();
}

Certificate* User::askCertificate (AC ac) {
	CertificateRequest request = new CertificateRequest();
	request.setSubject(rdnseq);
	request.setPublicKey(publkey);
	return ac.generateCertificate(request);
}

ByteArray User::sign(ByteArray document) {
	MessageDigest::init(MessaDigest::SHA512);
	MessageDigest digestor (MessageDigest::SHA512);
	ByteArray digest = digestor.doFinal(document);
	return Signer::sign(publkey, digest, MessageDigest::SHA512);

}

int main() {
	/* TEST */

	cout << "Prestes a gerar Autoridade Certificadora" << endl;
	AC ac = new AC("Autoridade Certificadora");
	cout << "Usuario sera criado" << endl;
	User user = new User("Joaozinho");
	cout << "Usuario ira pedir certificado" << endl;
	user.askCertificate(ac);
	cout << "Usuario recebeu o certificado" << endl;

}



