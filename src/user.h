#ifndef USER_H_
#define USER_H_

#include <libcryptosec/RSAKeyPair.h>
#include <libcryptosec/Signer.h>
#include <libcryptosec/ByteArray.h>
#include <libcryptosec/MessageDigest.h>
#include <libcryptosec/certificate/RDNSequence.h>
#include <libcryptosec/certificate/Certificate.h>
#include <libcryptosec/certificate/CertificateRequest.h>
#include "ac.h"

class User {
	public:
		User(std::string common_name);

		RDNSequence* rdnseq;
		RSAPublicKey* publkey;
		Certificate* certificate;

		void askCertificate(AC* ac);
		ByteArray sign(ByteArray document);
	
	protected:	
		CertificateRequest request;
		RSAPrivateKey* privkey;
};

#endif /*USER_H_*/
