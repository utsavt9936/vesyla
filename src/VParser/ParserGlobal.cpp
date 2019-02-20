
#include "ParserGlobal.hpp"

namespace GlobalValues
{
	char gInputFileName[80] = "";
	unsigned int gSourceLine = 1;
	const char* gFunctionName;

	bool gBisonDebug = true;
	bool gLexDebug = true;

	/* report mode has three values: 
		0: It just writes the report to the screen.
		1: It just writes the report to the log file.
		2: It writes both to the screen and the log file. */
	int gBisonReportMode = 1;
	int gLexReportMode = 1;
}
