#include <exception>
using namespace std;

#include "Register.hpp"
#include "BIRBase.hpp"

BIR::Register::Register()
{
	intValue = 0;
	realValue = 0.0;
	correspondingObject = 0;
	isFixedPoint = false;
}

