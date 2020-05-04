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
	
	AC* autoridade_certificadora = new AC("LabSecUFSC");

	MasterOperator* moperator = new MasterOperator("THE MASTER");
	
	list<NuclearOperator*> operator_list;
	for (int i = 3; i >= 0; --i) {
		std::string op_name = "opr" + to_string(i);
		operator_list.push_front( new NuclearOperator( op_name ) );
	}

	// Operadores pedem certificado
	
	moperator->askCertificate(autoridade_certificadora);
	for (	list<NuclearOperator*>::iterator opr = operator_list.begin();
		opr != operator_list.end(); opr++ ) 
	{
		(*opr)->askCertificate(autoridade_certificadora);
		
	}

	// Operador Master carrega o documento
	
	cout << moperator->loadDocument("./something.pdf") << endl;

	// Operador Master escolhe os operadores a assinar o documento
	
	list<Certificate*> cert_list;
	for (	list<NuclearOperator*>::iterator opr = operator_list.begin();
		opr != operator_list.end(); opr++ )	
	{
		cert_list.push_front((*opr)->certificate);
	}
	cert_list.push_front(moperator->certificate);

	cout << moperator->loadSigners(cert_list) << endl;

	// Operador Master pede assinaturas e verifica
	
	cout << moperator->sendSignatureRequests() << endl;
	cout << moperator->verifySignatureResponses() << endl;

	return 0;
}

