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
