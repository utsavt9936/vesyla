#include <exception>
using namespace std;

#ifndef __PragmaStatement_h__
#define __PragmaStatement_h__

// #include "BlockPragma.hpp"
#include "Statement.hpp"

namespace VIR
{
class BlockPragma;
// class Statement;
class PragmaStatement;
} // namespace VIR

namespace VIR
{
class PragmaStatement : public VIR::Statement
{
private:
	VIR::BlockPragma *_pragma;

public:
	PragmaStatement();

public:
	~PragmaStatement();

public:
	VIR::BlockPragma *pragma() const;
};
} // namespace VIR

#endif
