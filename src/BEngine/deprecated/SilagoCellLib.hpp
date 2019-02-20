#ifndef __VESYLA_BENGINE_SILAGO_CELL_LIB_HPP__
#define __VESYLA_BENGINE_SILAGO_CELL_LIB_HPP__

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <string>
#include <map>
#include "util/Common.hpp"

using namespace std;

namespace vesyla{
namespace bengine{

class SilagoCellLib{

public:
	struct CellConfig{
		int height;
		int width;
		int type;
	};

public:
	/**
	 * \brief Load XML formatted silago cell defination.
	 * \param path The path to file.
	 */
	void load(const string path);
	/**
	 * \brief Find the height (number of rows) of a cell.
	 * \param name The name of the cell.
	 * \return The height or -1 if the cell name is invalid.
	 */
	int get_height(const string name);
	/**
	 * \brief Find the width (number of columns) of a cell.
	 * \param name The name of the cell.
	 * \return The width or -1 if the cell name is invalid.
	 */
	int get_width(const string name);
	/**
	 * \brief Find the type id of a cell.
	 * \param name The name of the cell.
	 * \return The type id or -1 if the cell name is invalid.
	 */
	int get_type(const string name);

private:
	map<string, CellConfig> _silago_cell_map;
};

}
}
#endif // __VESYLA_BENGINE_PRIMITIVE_FUNC_LIB_HPP__
