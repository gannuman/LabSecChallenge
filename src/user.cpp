#include "user.h"

User::User(std::string common_name) {
	RDNSequence* rdnseq = new RDNSequence();
	rdnseq->addEntry(RDNSequence::COMMON_NAME, common_name);
	this->rdnseq = rdnseq;

	RSAKeyPair* keys = new RSAKeyPair(2048);
	ByteArray derPrivKey = keys->getPrivateKey()->getDerEncoded();
	this->privkey = new RSAPrivateKey(derPrivKey);
	ByteArray derPublKey = keys->getPublicKey()->getDerEncoded();
	this->publkey = new RSAPublicKey(derPublKey);
}

void User::askCertificate (AC* ac) {
	CertificateRequest* request = new CertificateRequest();
	request->setSubject(*this->rdnseq);
	request->setPublicKey(*this->publkey);
	this->certificate = ac->generateCertificate(*request);
}

ByteArray User::sign(ByteArray document) {
	MessageDigest::loadMessageDigestAlgorithms();
	MessageDigest digestor (MessageDigest::SHA512);
	ByteArray digest = digestor.doFinal(document);
	return Signer::sign(*this->privkey, digest, MessageDigest::SHA512);

}
