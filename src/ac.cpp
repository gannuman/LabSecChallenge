#include "ac.h"

AC::AC(std::string common_name) {
	RDNSequence rdnseq = new RDNSequence();   
	rdnseq.addEntry(RDNSequence::COMMON_NAME, common_name);

	RSAKeyPair keys = RSAKeyPair(2048);
	privkey = keys.getPrivateKey();
	publkey = keys.getPublicKey();
}

Certificate* AC::generateCertificate(CertificateRequest req) {
	CertificateBuilder certificator = new CertificateBuilder(req);
	// Configurando o certificado
	certificator.setIssuer(rdnseq);
	certificator.setSubject(req.getSubject);
	certificator.setPublicKey(req.getPublicKey);
	certificator.setSerialNumber((new BigInteger()).setRandValue);

	Certificate *signed_certificate = certificator.sing(privatekey, MessageDigest::SHA512);

	return signed_certificate;	
}
