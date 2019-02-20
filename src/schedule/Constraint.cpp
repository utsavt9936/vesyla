#include "Constraint.hpp"

namespace vesyla
{
namespace schedule
{

void Constraint::load(pt::ptree p)
{
	_src = p.get("src", "");
	_dest = p.get("dest", "");
	d_lo = p.get("d_lo", INT_MIN);
	d_hi = p.get("d_hi", INT_MAX);
	CHECK_NE(_src, "");
	CHECK_NE(_dest, "");
	CHECK_LE(d_lo, d_hi);
	CHECK(!((d_lo == INT_MIN) && (d_hi == INT_MAX)));
}

pt::ptree Constraint::dump()
{
	pt::ptree po;
	po.put("src", _src);
	po.put("dest", _dest);
	if (d_lo > INT_MIN)
	{
		po.put("d_lo", d_lo);
	}
	if (d_hi < INT_MAX)
	{
		po.put("d_hi", d_hi);
	}
	return po;
}

string Constraint::src()
{
	return _src;
}

string Constraint::dest()
{
	return _dest;
}

} // namespace schedule
} // namespace vesyla
