#ifndef MASTER_USER_H_
#define MASTER_USER_H_

#include <iostream>
#include <fstream>
#include <stdio.h>

#include "nuclear-operator.h"
#include "multi-sign-request.h"

class MasterOperator: public NuclearOperator {
	/* Essa classe representa um operador master
	 * de uma usina nuclear e sua interface com
	 * o sistema. Essa interface eh utilizada para
	 * operar o sistema na simulacao, simulando
	 * um login ao sistema por um usuario master.
	 * Esse usuario ira carregar um documento, 
	 * escolher os outros operadores que deverao
	 * assinar o documento, enviar o pedido e 
	 * verificar as assinaturas. */	
	public:
		MasterOperator(std::string common_name);

		std::string verifySignatureResponses();
		std::string sendSignatureRequests();
		std::string loadSigners(list<Certificate*> signers); 
		std::string loadDocument(std::string document_path);

	protected:
		MultiSignRequest* request;
};

#endif /* MASTER_USER_H_ */
