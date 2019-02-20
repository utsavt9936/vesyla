#include <exception>
#include <vector>
using namespace std;

#include "ReferencePragma.hpp"
#include "Coordinate.hpp"
#include "AssignmentPragma.hpp"

VIR::ReferencePragma::ReferencePragma() {
}

VIR::ReferencePragma::~ReferencePragma() {
//	throw "Not yet implemented";
}

vector<VIR::Expression*> & VIR::ReferencePragma::reference() {
	return _reference;
}

int VIR::ReferencePragma::parallelismSize() const {
	return coordinates.size();
}

