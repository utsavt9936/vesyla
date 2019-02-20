#include <exception>
using namespace std;

#include "Coordinate.hpp"
VIR::Coordinate::Coordinate(int row_, int column_, int bank_)
{
	row = row_;
	column = column_;
	bank = bank_;
}

VIR::Coordinate::Coordinate()
{
	row = -1;
	column = -1;
	bank = 0;
}

bool VIR::Coordinate::operator==(const VIR::Coordinate &coord_)
{
	return row == coord_.row && column == coord_.column && bank == coord_.bank;
}

bool VIR::Coordinate::operator!=(const VIR::Coordinate &coord_)
{
	return row != coord_.row || column != coord_.column || bank != coord_.bank;
}

string VIR::Coordinate::to_str()
{
	return (to_string(row) + "_" + to_string(column));
}

bool VIR::Coordinate::is_valid()
{
	if (row < 0 || column < 0)
	{
		return false;
	}
	return true;
}

void VIR::Coordinate::from_str(string s_)
{
	sscanf(s_.c_str(), "%d_%d", &row, &column);
}
