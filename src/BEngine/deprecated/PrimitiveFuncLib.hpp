#ifndef __VESYLA_BENGINE_PRIMITIVE_FUNC_LIB_HPP__
#define __VESYLA_BENGINE_PRIMITIVE_FUNC_LIB_HPP__

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <string>
#include <map>
#include "util/Common.hpp"

using namespace std;

namespace vesyla{
namespace bengine{

class PrimitiveFuncLib{

public:
	struct FuncConfig{
		int mode;
		int exec_cycle;
		map<int, int> arg_port;
		map<int, int> ret_port;
	};

public:
	/**
	 * \brief Load XML formatted primitive function defination.
	 * \param path The path to file.
	 */
	void load(const string path);
	/**
	 * \brief Find the DPU mode of a function.
	 * \param name The name of the function.
	 * \return The DPU mode or -1 if the function is invalid.
	 */
	int get_mode(const string name);
	/**
	 * \brief Find the execution cycle of a function.
	 * \param name The name of the function.
	 * \return The execution cycle or -1 if the function is invalid.
	 * \warning The returned execution cycle is the real execution cycle minus 1.
	 * e.g, ADD function will consume 1 clock cycle, the returned execution cycle
	 * for ADD should be zero.
	 */
	int get_exec_cycle(const string name);
	/**
	 * \brief Find the input port position of a function.
	 * \param name The name of the function.
	 * \param arg_pos The index of the argument.
	 * \return The input port position or -1 if the function or argument position
	 *         is invalid.
	 */
	int get_in_port(const string name, const int arg_pos);
	/**
	 * \brief Find the output port position of a function.
	 * \param name The name of the function.
	 * \param ret_pos The index of the returned value.
	 * \return The output port position or -1 if the function or return position
	 *         is invalid.
	 */
	int get_out_port(const string name, const int ret_pos);

private:
	map<string, FuncConfig> _primitive_func_map;
};

}
}
#endif // __VESYLA_BENGINE_PRIMITIVE_FUNC_LIB_HPP__
