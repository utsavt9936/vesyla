
#include "VParser.hpp"

#include "ParserGlobal.hpp"

//! Yu Yang 2017-08-01
// After move bison/flex generation to CMAKE, the header file name changes
// CHANGE BEGIN
#include "vparser.tab.hpp"
// CHANGE END

extern FILE *yyin;
extern int yydebug;
extern VIR::FunctionDeclaration *root;

using namespace GlobalValues;
using std::cout;

VIR::MainProgram *VParser::parse(const char *fileName_)
{
	// Get a file handle to a file
	FILE *inputfile;
	inputfile = fopen(fileName_, "r");

	// Make sure the file is valid
	if (!inputfile)
	{
		cout << "File not found: " << fileName_ << endl;
		return 0;
	}

	strncpy(gInputFileName, fileName_, 80);

	// Set lex to read from the file
	yyin = inputfile;

	// Debugging Configuration

	yydebug = 0;
	gLexDebug = true;
	gBisonDebug = true;
	gLexReportMode = 1;
	gBisonReportMode = 1;

	CREATE_NEW_LIBRARY;

	// Parsing
	yyparse();

	return dynamic_cast<VIR::MainProgram *>(root);
}
