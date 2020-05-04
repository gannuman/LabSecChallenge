#include "ac.h"

AC::AC(std::string common_name) {
	RDNSequence* rdnseq = new RDNSequence();   
	rdnseq->addEntry(RDNSequence::COMMON_NAME, common_name);
	this->rdnseq = rdnseq;

	RSAKeyPair keys = RSAKeyPair(2048);
	ByteArray derPrivKey = keys.getPrivateKey()->getDerEncoded();
	this->privkey = new RSAPrivateKey(derPrivKey);
	ByteArray derPublKey = keys.getPublicKey()->getDerEncoded();
	this->publkey = new RSAPublicKey(derPublKey);
}

Certificate* AC::generateCertificate(CertificateRequest& req) {
	CertificateBuilder* certificator = new CertificateBuilder(req);
	certificator->setIssuer(*this->rdnseq);
	
	Certificate* signed_certificate = certificator->sign(*this->privkey, MessageDigest::SHA512);
	this->certified_users.push_back(signed_certificate);
	return signed_certificate;	
}
