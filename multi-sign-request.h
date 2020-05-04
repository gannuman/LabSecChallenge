#ifndef MULTI_SIGN_REQUEST_H_
#define MULTI_SIGN_REQUEST_H_

#include <list>

#include <libcryptosec/MessageDigest.h>
#include <libcryptosec/Signer.h>
#include <libcryptosec/certificate/Certificate.h>

#include "nuclear-operator.h"

class MultiSignRequest {
		/* -~-~-~-~-~-~-~-~-~-~- */
		list<Certificate*> signers;
		list<ByteArray> signatures;
	
		void setSigners(list<Certificate*> signers);
		/* -~-~-~-~-~-~-~-~-~-~- */
		ByteArray* document;
		ByteArray* digest;
		void digestDocument();
		/* -~-~-~-~-~-~-~-~-~-~-~ */  	
		void askSignatures();
		bool verifySignatures();

		bool verified_positive;
		std::string verified_err;	
		/* -~-~-~-~-~-~-~-~-~-~-~ */
		friend class MasterUser;
	public:
		MultiSignRequest();
};

#endif /* MULTI_SIGN_REQUEST_H_ */
