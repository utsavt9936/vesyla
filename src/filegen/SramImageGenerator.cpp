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