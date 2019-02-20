#ifndef __VESYLA_SCHEDULE_ENGINE_HPP__
#define __VESYLA_SCHEDULE_ENGINE_HPP__

#include "Descriptor.hpp"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/copy.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/topological_sort.hpp>

namespace vesyla
{
namespace schedule
{
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, Operation, Constraint> Graph;
class Engine
{
public:
  Engine();
  Engine(Descriptor *ptr_desc_);
  ~Engine();

public:
  virtual bool schedule_graph(Graph &g_, Rot &global_rot_in_, int &min_end_time_) = 0;
};
} // namespace schedule
} // namespace vesyla

#endif // __VESYLA_SCHEDULE_ENGINE_HPP__