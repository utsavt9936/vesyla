#ifndef __VESYLA_SCHEDULE_CONSTRAINT_HPP__
#define __VESYLA_SCHEDULE_CONSTRAINT_HPP__

#include "util/Common.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace pt = boost::property_tree;

namespace vesyla{
namespace schedule{

class Constraint{
private:
	string _src;
	string _dest;
public:
	int d_lo;
	int d_hi;
	
	Constraint(const string src_="", const string dest_="", int d_lo_=INT_MIN, int d_hi_=INT_MAX): _src(src_), _dest(dest_), d_lo(d_lo_), d_hi(d_hi_){}
	void load(pt::ptree p);
	pt::ptree dump();
	string src();
	string dest();
};


}
}


#endif // __VESYLA_SCHEDULE_CONSTRAINT_HPP__
