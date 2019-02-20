

#ifndef  _FlexUtility_H_
# define _FlexUtility_H_

#include <stdlib.h>
#include <iostream>
#include <string>
#include "ParserGlobal.hpp"
#include "VManager/FileManager.hpp"

using std::string;
using std::cout;

inline char* realloc_string(char *buffer_, int length_)
{
  buffer_ = (char*) realloc(buffer_, length_);
  return buffer_; 
}

inline void printLexMessage(const string & message_)
{
	using namespace GlobalValues;

	if (gLexDebug)
		switch (gLexReportMode)
		{
			case 1: WriteLineToF(message_, ftParser, false); break;
			case 2: WriteLineToF(message_, ftParser, false);
			case 0: 
			default: cout << "\n" << message_;
		}
}

inline void printLexToken(const string & token_)
{
	string str = "FLEX: Source line: " + std::to_string(GlobalValues::gSourceLine) + ", returned token: " + token_;

	printLexMessage(str);
}

#endif // _FlexUtility_H_
