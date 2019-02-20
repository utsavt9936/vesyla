
#include "BisonUtility.hpp"
#include "VManager/FileManager.hpp"

FunctionDeclaration * root;

// Internal function for printing message according to the report mode
// In default mode, it uses the mode from global setting
inline void printMessage(const string & message, int reportMode = -1)
{
	using namespace GlobalValues;

	if (reportMode == -1)
		reportMode = gBisonReportMode;

	switch (reportMode)
	{
		case 1: WriteLineToF(message, ftParser, false); break;
		case 2: WriteLineToF(message, ftParser, false);
		case 0: 
		default: cout << "\n" << message;
	}
}

void fillArray(ArrayLinker *arrayLinker_, vector<Expression*> *exprList_)
{
	ArrayLinker *arrayLinker = arrayLinker_;
	ArrayLinker *nextLinker;

	while (true)
	{
		if (arrayLinker->prevElement)
			arrayLinker = arrayLinker->prevElement;
		else
			break;
	}
	while (arrayLinker)
	{
		exprList_->push_back(arrayLinker->element);
		nextLinker = arrayLinker->nextElement;
		delete arrayLinker;
		arrayLinker = nextLinker;
	}
}

void fillExpressionList(ExpressionLinker *exprLinker_, vector<Expression*> *exprList_)
{
	ExpressionLinker *exprLinker = exprLinker_;
	ExpressionLinker *nextLinker;

	while (exprLinker)
	{
		exprList_->push_back(exprLinker->expression);
		nextLinker = exprLinker->nextExpression;
		delete exprLinker;
		exprLinker = nextLinker;
	}
}

void fillStatementList(StatementLinker *stLinker_, vector<Statement*> *stList_)
{
	StatementLinker *stLinker = stLinker_;
	StatementLinker *nextLinker;
	while (stLinker)
	{
		stList_->push_back(stLinker->statement);
		nextLinker = stLinker->nextStatement;
		delete stLinker;
		stLinker = nextLinker;
	}
}

void fillNameList(NameLinker *nmLinker_, vector<Name*> *nmList_){
	NameLinker *nmLinker = nmLinker_;
	NameLinker *nextLinker;
	while(nmLinker){
		nmList_->push_back(nmLinker->name);
		nextLinker = nmLinker->nextName;
		delete nmLinker;
		nmLinker = nextLinker;
	}
}

/*! This function reports the error according to the current file, source line, and the given message. */
void reportError(const char *message)
{
	using namespace GlobalValues;

	string str = "Error ";

	str += "in \"" + string(gInputFileName) + "\" ";
	str += "around line (" + to_string(gSourceLine) + "): " + string(message) + "\n";

	printMessage(str, 2);
}

void printGrammar(const string & grammar_, const bool printLineNum_)
{
	if (GlobalValues::gBisonDebug)
	{
		string message = "BISON: " + 
			(printLineNum_ ? "source line: " + to_string(GlobalValues::gSourceLine) + ", " : "") + "grammar: " + grammar_;

		printMessage(message);
	}
}

int setPragmaOfAssignment(Statement * statement_, Pragma * pragma_)
{
	if (pragma_ != 0)
	{
		AssignmentStatement * assignmentSt = dynamic_cast<AssignmentStatement *> (statement_);

		if (assignmentSt)
			assignmentSt->pragma((AssignmentPragma*) pragma_);
		else
			return -1; // error occurred
	}	

	return 0;
}

int setPragmaOfFunctionCallStatement(FunctionCallStatement * statement_, Pragma * pragma_)
{
	if (pragma_ != 0)
	{
		FunctionCallStatement * st = dynamic_cast<FunctionCallStatement *> (statement_);

		if (st)
			st->pragma = (AssignmentPragma*) pragma_;
		else
			return -1; // error occurred
	}

	return 0;
}

void conv_slice_name_to_function_call(SliceName* slice_name, FunctionCall* function_call){
	function_call->_name = slice_name->prefix();
	function_call->_parameters = slice_name->suffix();
}
