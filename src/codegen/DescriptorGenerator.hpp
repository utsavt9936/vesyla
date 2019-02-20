#ifndef __VESYLA_CODEGEN_DESCRIPTOR_GENERATOR_HPP__
#define __VESYLA_CODEGEN_DESCRIPTOR_GENERATOR_HPP__

#include "util/Common.hpp"
#include "cidfg/CidfgGraph.hpp"
#include "schedule/Descriptor.hpp"

namespace vesyla
{
namespace codegen
{
class DescriptorGenerator
{
private:
	int _sn_counter;

public:
	DescriptorGenerator();
	~DescriptorGenerator();

public:
	schedule::Descriptor generate(cidfg::CidfgGraph &g_);

private:
	void gen_stage_0(cidfg::CidfgGraph &g_, schedule::Descriptor &d_);
	void gen_stage_1(cidfg::CidfgGraph &g_, schedule::Descriptor &d_);
	void gen_stage_1_callback(cidfg::CidfgGraph &g_, cidfg::CidfgGraph &new_g_, int id, int parent_id_, int child_index_, string parent_name_, std::set<int> &remove_vertices_, unordered_map<int, int> &hierarchical_instr_map_, unordered_map<int, vector<int>> &sub_vertex_map_);

	int get_lock_sn();
};
} // namespace codegen
} // namespace vesyla

#endif // __VESYLA_CODEGEN_DESCRIPTOR_GENERATOR_HPP__