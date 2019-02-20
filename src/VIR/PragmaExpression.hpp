#include <exception>
#include <string>
using namespace std;

#ifndef __PragmaExpression_h__
#define __PragmaExpression_h__

#include "Pragma.hpp"
#include "Expression.hpp"

namespace VIR
{
// class Pragma;
class PragmaExpression;
} // namespace VIR

namespace VIR
{
class PragmaExpression : public VIR::Pragma
{
private:
	string _name;

private:
	VIR::Expression *_row;

private:
	VIR::Expression *_column;

public:
	string name() const;

public:
	void name(const string &name_);

public:
	VIR::Expression *row() const;

public:
	void row(Expression *row_);

public:
	VIR::Expression *column() const;

public:
	void column(Expression *column_);
};
} // namespace VIR

#endif
