#include <exception>
using namespace std;

#ifndef __Register_h__
#define __Register_h__

#include "BIRBase.hpp"
#include "VIR/ObjectDeclaration.hpp"

namespace BIR
{
	// class BIRBase;
	class Register;
}

namespace BIR
{
	class Register: public BIR::BIRBase
	{
		public: int intValue;
		public: VIR::ObjectDeclaration * correspondingObject;
		public: float realValue;
		public: bool isFixedPoint;

		public: Register();
	};
}

#endif
