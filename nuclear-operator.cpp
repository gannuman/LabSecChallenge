#include "user.h"

NuclearOperator::NuclearOperator(std::string common_name) {
	MessageDigest::loadMessageDigestAlgorithms();

	RDNSequence* rdnseq = new RDNSequence();
	rdnseq->addEntry(RDNSequence::COMMON_NAME, common_name);
	this->rdnseq = rdnseq;

	this->keys = new RSAKeyPair(2048);
	ByteArray derPrivKey = this->keys->getPrivateKey()->getDerEncoded();
	ByteArray derPublKey = this->keys->getPublicKey()->getDerEncoded();
}

NuclearOperator::~NuclearOperator() {
	delete rdnseq;
	delete certificate;
	delete keys;
}

void NuclearOperator::askCertificate (AC* ac) {
	CertificateRequest* request = new CertificateRequest();
	request->setSubject(*this->rdnseq);
	request->setPublicKey(*this->keys->getPublicKey());
	this->certificate = ac->generateCertificate(*request);
	delete request;
}

ByteArray NuclearOperator::sign(ByteArray& digest) {
	return Signer::sign(*this->keys->getPrivateKey(), digest, MessageDigest::SHA512);
}
