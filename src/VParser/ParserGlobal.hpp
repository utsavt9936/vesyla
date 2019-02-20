
#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <fstream>

namespace GlobalValues
{
	extern char gInputFileName[80];
	extern std::ofstream gLogFile;
	extern unsigned int gSourceLine;

	extern bool gBisonDebug;
	extern bool gLexDebug;
	extern int gBisonReportMode;
	extern int gLexReportMode;
}

#endif // _GLOBAL_H_
