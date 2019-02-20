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


#ifndef _VParser_H_
#define _VParser_H_

#include "util/Common.hpp"
#include "VIR/VIRIncludeAll.hpp"
#include "VIR/MainProgram.hpp"
#include "VManager/MemoryManager.hpp"
#include <iostream>

#define PARSE(fileName) VParser::inst().parse(fileName);

class VParser
{
public:
	//! singleton implementation
	static VParser& inst() { static VParser vp; return vp; }

	VIR::MainProgram * parse(const char * fileName_);

private:
	//! singleton implementation
	VParser() {}
	VParser(VParser const&);
	void operator=(VParser const&);};

#endif // _VParser_H_
