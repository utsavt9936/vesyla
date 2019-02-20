#include "Timetable.hpp"

namespace vesyla
{
namespace schedule
{

string Timetable::dump()
{
	string s;
	for (auto &f : _table)
	{
		s += (f.dump() + " ");
	}
	return s;
}

void Timetable::shift(int offset_)
{
	for (auto &e : _table)
	{
		e.shift(offset_);
	}
}

bool Timetable::merge()
{
	sort(_table.begin(), _table.end(),
			 [](Frame a, Frame b) -> bool {
				 return (a.pos() < b.pos());
			 });

	vector<Frame> tb;
	for (auto &f : _table)
	{
		if (tb.size() == 0)
		{
			tb.push_back(f);
			continue;
		}
		Frame &f0 = tb.back();
		Frame &f1 = f;
		if (f0.type() == 1)
		{
			if (f1.type() == 1)
			{
				return false;
			}
			else if (f1.type() == 2)
			{
				if (f0.t1 == f1.t0 && f0.sn == f1.sn)
				{
					f0.t0 = f1.t0;
				}
				else if (f0.t1 < f1.t0)
				{
					tb.push_back(f1);
				}
				else
				{

					return false;
				}
			}
			else if (f1.type() == 3)
			{
				if (f0.t1 < f1.t0 && f1.t0 <= f1.t1)
				{
					tb.push_back(f1);
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else if (f0.type() == 2)
		{
			if (f1.type() == 1)
			{
				if (f0.t0 <= f1.t1 && f0.sn == f1.sn)
				{
					f0.t1 = f1.t1;
				}
				else
				{
					return false;
				}
			}
			else if (f1.type() == 2)
			{
				return false;
			}
			else if (f1.type() == 3)
			{
				return false;
			}
			else
			{
				return false;
			}
		}
		else if (f0.type() == 3)
		{
			if (f1.type() == 1)
			{
				return false;
			}
			else if (f1.type() == 2)
			{
				if (f0.t1 == f1.t0 - 1)
				{
					f0.t1 = f1.t1;
					f0.sn = f1.sn;
				}
				else if (f0.t1 < (f1.t0 - 1))
				{
					tb.push_back(f1);
				}
				else
				{
					return false;
				}
			}
			else if (f1.type() == 3)
			{
				if (f0.t1 == (f1.t0 - 1))
				{
					f0.t1 = f1.t1;
				}
				else if (f0.t1 < (f1.t0 - 1))
				{
					tb.push_back(f1);
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	_table = tb;
	return true;
}

} // namespace schedule
} // namespace vesyla
