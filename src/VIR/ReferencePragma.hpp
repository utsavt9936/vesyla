#include <exception>
#include <vector>
using namespace std;

#ifndef __ReferencePragma_h__
#define __ReferencePragma_h__

#include "Coordinate.hpp"
#include "AssignmentPragma.hpp"
#include "Expression.hpp"

namespace VIR {
class Coordinate;
// class AssignmentPragma;
class ReferencePragma;
}

namespace VIR {
class ReferencePragma: public VIR::AssignmentPragma {
private:
	vector<Expression*> _reference;
public:
	vector<VIR::Coordinate> coordinates;

public:
	ReferencePragma();

public:
	virtual ~ReferencePragma() = 0;

public:
	vector<Expression*> & reference();

public:
	int parallelismSize() const;
};
}

#endif
