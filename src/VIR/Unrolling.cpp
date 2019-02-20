#include <exception>
using namespace std;

#include "Unrolling.hpp"
VIR::Unrolling::Unrolling() {
	numberOfRepetitions = 0;
	unrollingOffset = 0;
	isDynamic = false;
}

