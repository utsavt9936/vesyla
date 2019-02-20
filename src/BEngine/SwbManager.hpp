#ifndef __VESYLA_BENGINE_SWB_MANAGER_HPP__
#define __VESYLA_BENGINE_SWB_MANAGER_HPP__

#include <map>
#include "BIR/SWBInstruction.hpp"

using namespace std;

namespace vesyla{
namespace bengine{

class SwbManager{
private:
	map<string, BIR::SWBInstruction*> _swb_status;
public:
	string get_signature(int row, int col, int type, int port);
	BIR::SWBInstruction* check_connection(string src, string dest);
	void update_connection(string src, string dest, BIR::SWBInstruction* instr);
	void clear();
};

}
}


#endif // __VESYLA_BENGINE_SWB_MANAGER_HPP__
