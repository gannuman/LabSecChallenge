#include "ac.h"

AC::AC(std::string common_name) {
	RDNSequence* rdnseq = new RDNSequence();   
	rdnseq->addEntry(RDNSequence::COMMON_NAME, common_name);
	this->rdnseq = rdnseq;

	this->keys = new RSAKeyPair(2048);
	this->publkey = keys->getPublicKey();
}

AC::~AC() {
	delete rdnseq;
	delete keys;
}

Certificate* AC::generateCertificate(CertificateRequest& req) {
	CertificateBuilder* certificator = new CertificateBuilder(req);
	certificator->setIssuer(*this->rdnseq);
	
	Certificate* signed_certificate = certificator->sign(*this->keys->getPrivateKey(), MessageDigest::SHA512);
	this->certified_users.push_back(signed_certificate);
	return signed_certificate;	
}
