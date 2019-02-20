#include <exception>
using namespace std;

#include "DPUPragma.hpp"
#include "../BIR/DPUMode.hpp"
#include "ReferencePragma.hpp"

VIR::DPUPragma::DPUPragma() {
	dpuMode = "";
	outPort = -1;
	saturation = false;
}

