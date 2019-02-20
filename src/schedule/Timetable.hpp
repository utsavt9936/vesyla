#ifndef __VESYLA_SCHEDULE_TIMETABLE_HPP__
#define __VESYLA_SCHEDULE_TIMETABLE_HPP__

#include "util/Common.hpp"
#include "Frame.hpp"

namespace vesyla{
namespace schedule{

//! A class that represent resource occupation status of one resource. It's a collection of Frame.
class Timetable{
private:
	vector<Frame> _table;
public:
	/**
	 * Constructor
	 */
	Timetable(vector<Frame> v_={}) : _table(v_){}
	Timetable(vector<vector<int> > v_){
		for(auto& e : v_){
			Frame f(e);
			_table.push_back(f);
		}
	}
	
	/**
	 * \brief Shift every frame in Timetable.
	 * \param offset_ The constant offset.
	 */
	void shift(int offset_);
	
	/**
	 * \brief Merge frame in Timetable if possible. If frames have conflict, report merge failure.
	 * \return True if merge is success, otherwise false.
	 */
	bool merge();
	
	/**
	 * \brief Dump the Timetable for debugging.
	 */
	string dump();
	
	using iterator = std::vector<Frame>::iterator;
	using const_iterator = std::vector<Frame>::const_iterator;

	/**
	 * \brief Interface for iteration
	 */
	iterator begin(){
		return _table.begin();
	}
	
	/**
	 * \brief Interface for iteration
	 */
	iterator end(){
		return _table.end();
	}
	
	/**
	 * \brief Interface for iteration
	 */
	const_iterator cbegin() const {
		return _table.cbegin();
	}
	
	/**
	 * \brief Interface for iteration
	 */
	const_iterator cend() const {
		return _table.cend();
	}
	
	/**
	 * \brief Interface vector like push back
	 */
	void push_back(Frame f_){
		_table.push_back(f_);
	}
	
	/**
	 * \brief Interface for vector like size access.
	 */
	int size(){
		return _table.size();
	}
	
	/**
	 * \brief Interface for vector like slicing.
	 */
	Frame& operator[](const int i){
		return _table[i];
	}
	
};

}
}

#endif // __VESYLA_SCHEDULE_TIMETABLE_HPP__
