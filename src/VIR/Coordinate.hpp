#include <exception>
using namespace std;

#ifndef __Coordinate_h__
#define __Coordinate_h__

#include "util/Common.hpp"

namespace VIR
{
class Coordinate;
}

namespace VIR
{
class Coordinate
{
public:
	int row;
	int column;
	int bank;

public:
	Coordinate(int row_, int column_, int bank_ = 0);
	Coordinate();

public:
	bool operator==(const VIR::Coordinate &coord_);
	bool operator!=(const VIR::Coordinate &coord_);
	string to_str();
	bool is_valid();
	void from_str(string s_);
};
} // namespace VIR

#endif
