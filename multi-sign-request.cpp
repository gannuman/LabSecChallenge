#include "multi-sign-request.h"

MultiSignRequest::MultiSignRequest() {
	this->verified_positive = false;
	this->verified_err = "ok";
}


void MultiSignRequest::setSigners(list<Certificate*> signers) {
	this->signers = signers;
}

void MultiSignRequest::digestDocument() {
	MessageDigest digestor (MessageDigest::SHA512);
	this->digest = digestor.doFinal(this->document);
}

void MultiSignRequest::askSignatures() {
	for (std::list<NuclearOperator>::iterator it = this->signers.begin(); it != this->signers.end(); it++) {
			signatures.push_front(it->sign(*this->document_digested));
	}
}

bool MultiSignRequest::verifySignatures() {
	if (signatures.size != signers.size) {
		this->verified_err = "Algum Operador Nuclear nao assinou o documento.";
		return;
	}
	int verified_count = 0;
	for (std::list<Certifacate>::iterator signer = this->signers.begin(); signer != this->signers.end(); signer++) {
		for (std::list<ByteArray>::iterator signature = this->signatures.begin(); signature != this->signatures.end(); signature++) {
			PublicKey* pkey = *signer.getPublicKey();
			if(Signer::verify(*pkey, *signature, *this->digest, MessageDigest::SHA512)) {
					verified_count++;
					break;
			}				
		}
	}
	if (verified_count == this->signers.size) {
		this->verified_positive = true;
		this->verified_err = "ok";
	} else {
		this->verified_err = "Alguma assinatura eh invalida.";
	}
	return this->verified_positive;
}
