#include <exception>
using namespace std;

#ifndef __SliceName_h__
#define __SliceName_h__

#include "Name.hpp"
#include "Identifier.hpp"
#include "IndexInfo.hpp"
#include "Address.hpp"

namespace VIR
{
// class Name;
class SliceName;
} // namespace VIR

namespace VIR
{
class SliceName : public VIR::Name
{
private:
	VIR::Identifier *_prefix;
	vector<Expression *> _suffix;
	VIR::IndexInfo *_indexInfo;

public:
	VIR::Address addr;

public:
	bool is_function_call;

public:
	SliceName();

public:
	VIR::Identifier *prefix() const;

public:
	void prefix(Identifier *prefix_);

public:
	vector<Expression *> &suffix();

public:
	VIR::IndexInfo *indexInfo() const;

public:
	void indexInfo(VIR::IndexInfo *indexInfo_);
};
} // namespace VIR

#endif
