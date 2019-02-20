#include <exception>
#include <string>
#include <map>
using namespace std;

#ifndef __ForStatement_h__
#define __ForStatement_h__

#include "ControlStatement.hpp"
#include "ParallelMode.hpp"
#include "RangeExpression.hpp"
#include "Identifier.hpp"
#include "BIR/Instruction.hpp"
#include "Coordinate.hpp"

namespace VIR
{
// class ControlStatement;
namespace VirEnumerations
{
// enum ParallelMode;
}
} // namespace VIR

namespace VIR
{
class ForStatement : public VIR::ControlStatement
{
private:
	RangeExpression *_loopRange;

private:
	VIR::Identifier *_loopVariable;

private:
	vector<Statement *> _loopBody;

private:
	VIR::VirEnumerations::ParallelMode _parallelMode;

private:
	int _degree;

private:
	int _repetition;

private:
	bool _isConstant;

private:
	bool _needDynamicHandling;

private:
	map<string, int> _unrolledRepetitionsMap;

public:
	vector<BIR::Instruction *> head_raccu_list;
	vector<BIR::Instruction *> tail_raccu_list;
	vector<Coordinate> head_raccu_coord_list;
	vector<Coordinate> tail_raccu_coord_list;

public:
	ForStatement();

public:
	VIR::RangeExpression *loopRange() const;

public:
	void loopRange(RangeExpression *loopRange_);

public:
	VIR::Identifier *loopVariable() const;

public:
	void loopVariable(Identifier *loopVariable_);

public:
	vector<Statement *> &loopBody();

public:
	VIR::VirEnumerations::ParallelMode parallelMode() const;

public:
	void parallelMode(const VIR::VirEnumerations::ParallelMode &parallelMode_);

public:
	int degree() const;

public:
	void degree(int degree_);

public:
	int repetition() const;

public:
	void repetition(int repetition_);

public:
	bool isConstant() const;

public:
	void isConstant(bool isConstant_);

public:
	bool needDynamicHandling() const;

public:
	void needDynamicHandling(bool needDynamicHandling_);

public:
	map<string, int> &unrolledRepetitionsMap();

public:
	void add_head_raccu_instr(BIR::Instruction *instr_, Coordinate coord_)
	{
		head_raccu_list.push_back(instr_);
		head_raccu_coord_list.push_back(coord_);
	}
	void add_tail_raccu_instr(BIR::Instruction *instr_, Coordinate coord_)
	{
		tail_raccu_list.push_back(instr_);
		tail_raccu_coord_list.push_back(coord_);
	}
};
} // namespace VIR

#endif
