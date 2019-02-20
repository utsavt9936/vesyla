#ifndef __VESYLA_SCHEDULE_NAIVE_ENGINE_HPP__
#define __VESYLA_SCHEDULE_NAIVE_ENGINE_HPP__

#include "Engine.hpp"
#include <boost/graph/graph_traits.hpp>

namespace vesyla
{
namespace schedule
{
class NaiveEngine : public Engine
{
public:
	NaiveEngine();
	NaiveEngine(Descriptor *ptr_desc_);
	~NaiveEngine();

public:
	bool schedule_graph(Graph &g, Rot &global_rot_in, int &min_end_time);
};
} // namespace schedule
} // namespace vesyla

#endif // __VESYLA_SCHEDULE_NAIVE_ENGINE_HPP__