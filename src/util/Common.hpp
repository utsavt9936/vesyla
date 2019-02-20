#ifndef __VESYLA_UTIL_COMMON_HPP__
#define __VESYLA_UTIL_COMMON_HPP__

#include "easylogpp/easylogging++.h"
#include "json/json.hpp"
#include "inja/inja.hpp"
#include "GlobalVar.hpp"
#include <string.h>
#include <vector>
#include <map>
#include <unordered_map>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <cfloat>
#include <math.h>

#include "SysPath.hpp"
#include "Config.hpp"

#define __NOT_IMPLEMENTED__ LOG(FATAL) << "Function has not been implemented yet!";
#define __NOT_SUPPORTED__ LOG(FATAL) << "Function is not supported!";
#define __DEPRECATED__ LOG(WARNING) << "Function is deprecated and will be removed soon!";

class Common
{
public:
	// __BLANK__;
};

#endif // __VESYLA_UTIL_COMMON_HPP__
