#include "Engine.hpp"

namespace vesyla
{
namespace schedule
{
Engine::Engine() {}
Engine::Engine(Descriptor *ptr_desc_) {}
Engine::~Engine() {}
bool Engine::schedule_graph(Graph &g_, Rot &global_rot_in_, int &min_end_time_) {}
} // namespace schedule
} // namespace vesyla
