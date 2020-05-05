#ifndef MULTI_SIGN_REQUEST_H_
#define MULTI_SIGN_REQUEST_H_

#include <list>

#include <libcryptosec/MessageDigest.h>
#include <libcryptosec/Signer.h>
#include <libcryptosec/certificate/Certificate.h>

#include "nuclear-operator.h"
#include "ac.h"

class MultiSignRequest {
	public:	
		MultiSignRequest();
		/* -~-~-~-~-~-~-~-~-~-~- */
		list<NuclearOperator*> signers;
		list<ByteArray> signatures;
	
		void setSigners(list<NuclearOperator*> signers);
		/* -~-~-~-~-~-~-~-~-~-~- */
		ByteArray* document;
		ByteArray digest;
		void digestDocument();
		/* -~-~-~-~-~-~-~-~-~-~-~ */  	
		void askSignatures();
		bool verifySignatures(AC* ac);

		bool verified_positive;
		std::string verified_err;	
};

#endif /* MULTI_SIGN_REQUEST_H_ */
