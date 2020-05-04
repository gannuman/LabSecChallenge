#ifndef NUCLEAR_OPERATOR_H_
#define NUCLEAR_OPERATOR_H_

#include <libcryptosec/RSAKeyPair.h>
#include <libcryptosec/Signer.h>
#include <libcryptosec/ByteArray.h>
#include <libcryptosec/MessageDigest.h>
#include <libcryptosec/certificate/RDNSequence.h>
#include <libcryptosec/certificate/Certificate.h>
#include <libcryptosec/certificate/CertificateRequest.h>
#include "ac.h"

class NuclearOperator {
	/* Essa classe representa um operador de usina
	 * nuclear e sua interface com o sistema. */
	public:
		NuclearOperator(std::string common_name);

		RDNSequence* rdnseq;
		Certificate* certificate;

		void askCertificate(AC* ac);
		ByteArray sign(ByteArray& digest);
	 
	protected:	
		CertificateRequest request;
		RSAKeyPair* keys;
};

#endif /* NUCLEAR_OPERATOR_H_ */
