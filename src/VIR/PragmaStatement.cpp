#include <exception>
using namespace std;

#include "PragmaStatement.hpp"
#include "BlockPragma.hpp"
#include "Statement.hpp"

VIR::PragmaStatement::PragmaStatement() {
	_pragma = new BlockPragma();
}

VIR::PragmaStatement::~PragmaStatement() {
	delete _pragma;
}

VIR::BlockPragma * VIR::PragmaStatement::pragma() const {
	return _pragma;
}

