#include "master-operator.h"

MasterOperator::MasterOperator(std::string common_name):NuclearOperator(common_name) {
	this->request = new MultiSignRequest();
}

MasterOperator::~MasterOperator() {
	delete this->request;
}

std::string MasterOperator::verifySignarureResponse() {
	if( this->request.verifySignatures() ) {
		return "As assinaturas sao legitimas!";
	} else {
		return this->request.verified_err;
	}
}

std::string MasterOperator::sendSignatureRequests() {
	return this->request.askSignatures();
}

std::string MasterOperator::loadSigners(list<Certificate>& signers) {
	return this->request.setSigners(signers);
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
	this->request.documet = new ByteArray(memblock);
	this->request.digestDocument();
}
