#ifndef __VESYLA_CIDFG_OBJECT_HPP__
#define __VESYLA_CIDFG_OBJECT_HPP__

#include "util/Common.hpp"

namespace vesyla
{
namespace cidfg
{

/**
	* The base class which derives all other classes in cidfg.
	* It just maintains an ID of any cidfg object.
	* The ID will NOT be automatically assigned while creation because temperary used objects don't worth to waste available IDs.
	* Only when being added to a cidfg graph, an Object's id field will be set. 
	* \warning This is an abstract class, one should never use this class directly.
	*/
class Object
{
public:
	static int id_counter; ///< Static property used only for generating new id
	int id;								 ///< The id in a cidfg graph

public:
	Object();
	virtual ~Object() = 0;
};

} // namespace cidfg
} // namespace vesyla

#endif // __VESYLA_CIDFG_OBJECT_HPP__