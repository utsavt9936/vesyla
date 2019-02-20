#include <exception>
#include <string>
using namespace std;

#include "PragmaExpression.hpp"
#include "Pragma.hpp"

string VIR::PragmaExpression::name() const {
	return _name;
}

void VIR::PragmaExpression::name(const string & name_) {
	_name = name_;
}

VIR::Expression * VIR::PragmaExpression::row() const {
	return _row;
}

void VIR::PragmaExpression::row(Expression * row_) {
	_row = row_;
}

VIR::Expression * VIR::PragmaExpression::column() const {
	return _column;
}

void VIR::PragmaExpression::column(Expression * column_) {
	_column = column_;
}

