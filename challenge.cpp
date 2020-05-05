#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <stdio.h>
#include <libcryptosec/MessageDigest.h>
#include <libcryptosec/ByteArray.h>
#include <libcryptosec/Signer.h>
#include <libcryptosec/KeyPair.h>
#include <libcryptosec/AsymmetricKey.h>
#include "master-operator.h"
#include "ac.h"

using namespace std;


int main(int argc, char **argv) {

	cout << "Ola :)" << endl;
	cout << "Esse programa ira simular a situacao de assinaturas multiplas." << endl;
	cout << "Um operador master ira carregar um documento que devera ser assinado" << endl;
	cout << "por multiplos operadores de uma usina nuclear." << endl;
	cout << "Durante a execucao do programa os operadores irao pedir um" << endl;
	cout << "certificado digital para um Autoridade Certificadora e assinar" << endl;
	cout << "o documento. O operador master ira verificar os certificados e" << endl;
	cout << "as assinaturas." << endl;
	cout << endl << "---------------------------------------------------------------" << endl << endl;
	cout << "Vamos la!" << endl << endl;

	// Cria entidades

	AC* autoridade_certificadora = new AC("LabSecUFSC");
	MasterOperator* moperator = new MasterOperator("THE MASTER");

	cout << "Quantos operadores, incluindo o master, devem existir?" << endl;
	int opr_count;
	cin >> opr_count;

	list<NuclearOperator*> operator_list;
	for (int i = opr_count - 1; i > 0; --i) {
		std::string op_name = "opr" + to_string(i);
		operator_list.push_front( new NuclearOperator( op_name ) );
	}
	operator_list.push_front(moperator);

	cout << "Os operadores foram criados e irao pedir certificados para a AC." << endl;

	// Operadores pedem certificado
	
	for (	list<NuclearOperator*>::iterator opr = operator_list.begin();
		opr != operator_list.end(); opr++ ) 
	{
		cout << (*opr)->askCertificate(autoridade_certificadora) << " ganha certificado" << endl;
		
	}

	// Operador Master carrega o documento
	
	cout << "Operador master ira carregar o documento." << endl;
	cout << "Qual documento deve ser carregado?" << endl;
	string doc_path;
	bool file_exists = false;
	
	while(!file_exists) {
		cin >> doc_path;
			
		ifstream file(doc_path);
		if(!file) {
			cout << "Esse arquivo nao existe, entre um arquivo valido." << endl;
			file_exists = false;
		} else                 
			file_exists = true; 
	}
	cout << moperator->loadDocument("./something.pdf") << endl;

	// Operador Master escolhe os operadores a assinar o documento
	
	cout << moperator->loadSigners(operator_list) << endl;

	// Operador Master pede assinaturas e verifica
	
	cout << moperator->sendSignatureRequests() << endl;
	cout << moperator->verifySignatureResponses(autoridade_certificadora) << endl;

	return 0;
}

