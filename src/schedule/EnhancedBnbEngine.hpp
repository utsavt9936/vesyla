#ifndef __VESYLA_SCHEDULE_ENHANCED_BNB_ENGINE_HPP__
#define __VESYLA_SCHEDULE_ENHANCED_BNB_ENGINE_HPP__

#include "Engine.hpp"
#include <boost/graph/graph_traits.hpp>

namespace vesyla
{
namespace schedule
{
class EnhancedBnbEngine : public Engine
{
public:
	EnhancedBnbEngine();
	EnhancedBnbEngine(Descriptor *ptr_desc_);
	~EnhancedBnbEngine();

public:
	bool schedule_graph(Graph &g, Rot &global_rot_in, int &min_end_time);
	bool schedule_graph_callback(Graph &g, Rot &global_rot_in, int &min_end_time);
};
} // namespace schedule
} // namespace vesyla

#endif // __VESYLA_SCHEDULE_ENHANCED_BNB_ENGINE_HPP__