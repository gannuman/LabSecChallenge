#include "master-operator.h"

MasterOperator::MasterOperator(std::string common_name):NuclearOperator(common_name) {
	this->request = new MultiSignRequest();
}

MasterOperator::~MasterOperator() {
	delete this->request;
}

std::string MasterOperator::verifySignatureResponses(AC* ac) {
	if( this->request->verifySignatures(ac) ) {
		return "As assinaturas sao legitimas!";
	} else {
		return this->request->verified_err;
	}
}

std::string MasterOperator::sendSignatureRequests() {
	this->request->askSignatures();
	return "Pedidos de assinatura enviados, assinaturas criadas e devolvidas.";
}

std::string MasterOperator::loadSigners(list<NuclearOperator*> signers) {
	this->request->setSigners(signers);
	return "Operadores assinantes selecionados.";
}

std::string MasterOperator::loadDocument(std::string document_path) {
	streampos size;
	char* memblock;

	ifstream file (document_path, ios::in | ios::ate | ios::binary);
	if (file.is_open()) {
		size = file.tellg();
		memblock = new char [size];
		file.read (memblock, size);
		file.close();
	}
	this->request->document = new ByteArray(memblock);
	this->request->digestDocument();
	return "Documento carregado e digerido.";
}
