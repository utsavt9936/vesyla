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

#include "SramImageGenerator.hpp"
namespace vesyla
{
namespace filegen
{
void SramImageGenerator::generate(map<string, SRAM *> sram_lists_, string filename_)
{
	ofstream ofs(filename_, ofstream::out);
	for (auto &e : sram_lists_)
	{
		string cell_str = e.first;
		vector<string> coord;
		boost::split(coord, cell_str, boost::is_any_of("_"));
		string str = "CELL <" + coord[0] + "," + coord[1] + ">";
		Common::write_line(ofs, str);

		for (int i = 0; i < e.second->depth(); i++)
		{
			string str = "";
			BIR::MemElement *ele = e.second->memory(i);
			for (int j = 0; j < e.second->width() / 16; j++)
			{
				int num = 0;
				if (ele->isFixedPoint())
				{
					num = (int)(ele->realValues()[j] * (1 << 15));
				}
				else
				{
					num = ele->intValues()[j];
				}
				if (num > (1 << 15) - 1)
				{
					num = (1 << 15) - 1;
				}
				else if (num < -(1 << 15))
				{
					num = -(1 << 15);
				}
				std::stringstream ss;
				ss << std::hex << setfill('0') << setw(4) << std::uppercase << num;
				str = ss.str() + str;
			}
			Common::write_line(ofs, str);
		}
	}
}
} // namespace filegen
} // namespace vesyla