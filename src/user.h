#ifndef USER_H_
#define USER_H_

#include <libcryptosec/RDNSequence>
#include <libcryptosec/RSAKeyPair>
#include <libcryptosec/Signer>
#include <libcryptosec/ByteArray>
#include <libcryptosec/MessageDigest>
#include <libcryptosec/CertificateRequest>
#include "ac.h"


class User {
	public:
		User(std::string common_name);

		RDNSequence rdnseq;
		RSAPublicKey publkey;
		Certificate certificate;

		Certificate* askCertificate(AC ac);
		ByteArray sign(ByteArray document);
	
	protected:	
		RSAPrivateKey privkey;
}

#endif /*USER_H_*/
