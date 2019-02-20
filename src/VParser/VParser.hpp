
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
