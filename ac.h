#ifndef AC_H_
#define AC_H_

#include <list>

#include <libcryptosec/certificate/RDNSequence.h>
#include <libcryptosec/RSAKeyPair.h>
#include <libcryptosec/certificate/CertificateBuilder.h>
#include <libcryptosec/certificate/CertificateRequest.h>
#include <libcryptosec/certificate/Certificate.h>

class AC {
	public:
		RDNSequence* rdnseq;
		PublicKey* publkey;

		AC(std::string common_name);

		Certificate* generateCertificate(CertificateRequest& req);

		~AC();

	protected:
		RSAKeyPair* keys;
		list<Certificate*> certified_users;
};

#endif /* AC_H_ */
