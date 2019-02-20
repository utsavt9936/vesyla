#include <exception>
using namespace std;

#include "AddressInfo.hpp"
#include "ForStatement.hpp"

VIR::AddressInfo::AddressInfo() {
	startAddress = 0;
	increment = 0;
	numberOfAddress = 0;
	numberOfRepetitions = 0;
	repetitionOffset = 0;
	is1stLevelDynamic = false;
	is2ndLevelDynamic = false;
	firstLevelLoop = 0;
	secondLevelLoop = 0;
}

