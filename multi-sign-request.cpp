#include "multi-sign-request.h"

MultiSignRequest::MultiSignRequest() {
	this->verified_positive = false;
	this->verified_err = "ok";
}


void MultiSignRequest::setSigners(list<NuclearOperator*> signers) {
	this->signers = signers;
}

void MultiSignRequest::digestDocument() {
	MessageDigest digestor (MessageDigest::SHA512);
	this->digest = digestor.doFinal(*this->document);
}

void MultiSignRequest::askSignatures() {
	for (std::list<NuclearOperator*>::iterator it = this->signers.begin(); it != this->signers.end(); it++) {
			this->signatures.push_front((*it)->sign(this->digest));
	}
}

bool MultiSignRequest::verifySignatures(AC* ac) {
	if (signatures.size() != signers.size()) {
		this->verified_err = "Algum Operador Nuclear nao assinou o documento.";
		return false;
	}
	int verified_count = 0;
	for (std::list<NuclearOperator*>::iterator signer = this->signers.begin(); signer != this->signers.end(); signer++) {
		for (std::list<ByteArray>::iterator signature = this->signatures.begin(); signature != this->signatures.end(); signature++) {
			PublicKey* pkey = (*signer)->certificate->getPublicKey();
			// Verifica assinatura e certificado do assinante
			if(Signer::verify(*pkey, *signature, this->digest, MessageDigest::SHA512)
				&& (*signer)->certificate->verify(*ac->publkey)) 
			{
				verified_count++;
				break;
			}				
		}
	}
	if (verified_count == this->signers.size()) {
		this->verified_positive = true;
		this->verified_err = "ok";
	} else {
		this->verified_err = "Alguma assinatura eh invalida.";
	}
	return this->verified_positive;
}
