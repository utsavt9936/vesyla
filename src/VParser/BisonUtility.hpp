// Copyright (C) 2019 Yu Yang
// 
// This file is part of Vesyla.
// 
// Vesyla is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Vesyla is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Vesyla.  If not, see <http://www.gnu.org/licenses/>.



#ifndef _BisonUtility_H_
#define _BisonUtility_H_

#include <string>
#include <iostream>
#include "ParserGlobal.hpp"
#include "VIR/VIRIncludeAll.hpp"

using std::cout;
using namespace VIR;

extern FunctionDeclaration * root;

struct ArrayLinker
{
	Expression *element;
	ArrayLinker *prevElement;
	ArrayLinker *nextElement;

	ArrayLinker(Expression *elem, ArrayLinker *prevElem, ArrayLinker *nextElem) :
		element(elem), prevElement(prevElem), nextElement(nextElem) {}
};

struct ExpressionLinker
{
	Expression *expression;
	ExpressionLinker *nextExpression;

	ExpressionLinker(Expression *expr, ExpressionLinker *nextExpr) :
		expression(expr), nextExpression(nextExpr) {}
};

struct StatementLinker
{
	Statement *statement;
	StatementLinker *nextStatement;

	StatementLinker(Statement *st, StatementLinker *nextSt) :
		statement(st), nextStatement(nextSt) {}
};

struct NameLinker{
	Name *name;
	NameLinker *nextName;
	NameLinker(Name* nm, NameLinker *nextNm) : name(nm), nextName(nextNm){}
};

void fillArray(ArrayLinker *arrayLinker_, vector<Expression*> *exprList_);

void fillExpressionList(ExpressionLinker *exprLinker_, vector<Expression*> *exprList_);

void fillStatementList(StatementLinker *stLinker_, vector<Statement*> *stList_);

void fillNameList(NameLinker *nmLinker_, vector<Name*> *nmList_);

void reportError(const char *message);

void printGrammar(const string & grammar_, const bool printLineNum_ = false);

int setPragmaOfAssignment(Statement * statement_, Pragma * pragma_);

int setPragmaOfFunctionCallStatement(FunctionCallStatement * statement_, Pragma * pragma_);

void conv_slice_name_to_function_call(SliceName* slice_name, FunctionCall* function_call);


#endif // _BisonUtility_H_
