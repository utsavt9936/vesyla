#include <exception>
using namespace std;

#include "RaccuPragma.hpp"
#include "../BIR/RACCUMode.hpp"
#include "AssignmentPragma.hpp"
#include "RaccuOptions.hpp"

VIR::RaccuPragma::RaccuPragma() {
	raccuMode = BIR::BIREnumerations::rmUnspecified;
	raccuOptions = VIR::VirEnumerations::roNone;
}

