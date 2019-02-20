#include <exception>
using namespace std;

#ifndef __AssignmentStatement_h__
#define __AssignmentStatement_h__

#include "Statement.hpp"
#include "AssignmentType.hpp"
#include "Name.hpp"
#include "SliceName.hpp"
#include "Identifier.hpp"
#include "BIR/Instruction.hpp"

namespace VIR
{
// class Statement;
class AssignmentStatement;
namespace VirEnumerations
{
// enum AssignmentType;
}
} // namespace VIR

namespace VIR
{
class AssignmentStatement : public VIR::Statement
{
public:
	vector<VIR::Name *> _lhs;
	VIR::Expression *_rhs;
	VIR::AssignmentPragma *_pragma;
	vector<SliceName *> _rhsSliceNames;
	vector<Identifier *> _rhsIdentifiers;
	vector<VIR::Identifier *> _lhsIdentifiers;
	vector<VIR::SliceName *> _lhsSliceNames;
	VIR::VirEnumerations::AssignmentType _type;
	VIR::AssignmentStatement *_twinStatement;
	bool _isLastResSharingStatement;
	string function_name;

public:
	vector<BIR::Instruction> translated_instructions;

public:
	AssignmentStatement();

public:
	vector<VIR::Name *> &lhs();
	void lhs(vector<Name *> lhs_);
	VIR::Expression *rhs() const;
	void rhs(Expression *rhs_);
	VIR::AssignmentPragma *pragma() const;
	void pragma(AssignmentPragma *pragma_);
	vector<SliceName *> &rhsSliceNames();
	vector<Identifier *> &rhsIdentifiers();
	vector<SliceName *> &lhsSliceNames();
	vector<VIR::Identifier *> &lhsIdentifiers();

	VIR::VirEnumerations::AssignmentType type() const;
	void type(VIR::VirEnumerations::AssignmentType type_);

	VIR::AssignmentStatement *twinStatement() const;
	void twinStatement(VIR::AssignmentStatement *twinStatement_);
	bool isLastResSharingStatement() const;
	void isLastResSharingStatement(bool isLastResSharingStatement_);
};
} // namespace VIR

#endif
