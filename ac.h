#ifndef AC_H_
#define AC_H_

#include <list>

#include <libcryptosec/Certificate>
#include <libcryptosec/CertificateBuilder>
#include <libcryptosec/CertificateRequest>
#include <libcryptosec/RDNSequence>
#include <libcryptosec/BigInteger>
#include <libcryptosec/MessageDigest>

class AC {
	public:
		AC(std::string common_name);

		RDNSequence rdnseq;
		RSAPublicKey publkey;

		Certificate* generateCertificate(CertificateRequest req);

	protected:
		RSAPrivateKey privkey;
		list<Certificate> cert_list;
}

#endif /*AC_H_*/
