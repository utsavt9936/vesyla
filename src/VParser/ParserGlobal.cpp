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
