#include "DependencyGraph.hpp"

namespace vesyla{
namespace schedule{

void DependencyGraph::add_vertex(DependencyGraph::Vertex& _v){
	for(auto& v : _vertex_list){
		if(v.id == _v.id){
			LOG(FATAL) << "Conflict id in graph!";
		}
	}
	_vertex_list.push_back(_v);
}

bool DependencyGraph::add_edge(DependencyGraph::Edge& _e){
	DependencyGraph::Vertex v1 = find_vertex(_e.src_id);
	DependencyGraph::Vertex v2 = find_vertex(_e.dest_id);
	if(v1.id<0 || v2.id<0){
		cout << "Vertex in edge doesn't exist!" << endl;
		return false;
	}
	_edge_list.push_back(_e);
	return true;
}

void DependencyGraph::dump(){
	cout << left << setw(4) << "ID" << setw(20) << "NAME" << setw(8) << "START" << setw(10) << "PACK" << endl;
	cout << "------------------------------------------------------" << endl;
	for(auto& v : _vertex_list){
		cout << left << setw(4) << v.id << setw(20) << v.name << setw(8) << v.start << setw(10) << to_string(v.pack_id)+"("+to_string(v.pack_offset)+")" << endl;
	}
	cout << endl;
	cout << left << setw(4) << "SRC"  << "-> " << setw(6) << "DEST" << setw(8) << "TYPE" << setw(8) << "DISTANCE" << endl;
	cout << "------------------------------------------------------" << endl;
	for(auto& v : _edge_list){
		cout << left << setw(4) << v.src_id << "-> "<<  setw(6) << v.dest_id << setw(8) << v.link_type << setw(8) << v.distance << endl;
	}
}

DependencyGraph::Vertex& DependencyGraph::find_vertex(int _id){
	for(auto& v : _vertex_list){
		if(v.id == _id){
			return v;
		}
	}
	cout << "ERROR! Can't find vertex: " << _id << endl;
	exit(-1);
}

vector<int> DependencyGraph::find_predecessors(int _id){
	vector<int> vec;
	for(auto& e : _edge_list){
		if(e.dest_id == _id){
			vec.push_back(e.src_id);
		}
	}
	return vec;
}

vector<int> DependencyGraph::find_successors(int _id){
	vector<int> vec;
	for(auto& e : _edge_list){
		if(e.src_id == _id){
			vec.push_back(e.dest_id);
		}
	}
	return vec;
}

void DependencyGraph::calculate_pack_offset(int _id){
	Vertex& v = find_vertex(_id);

	for(auto& e : _edge_list){
		if(e.link_type == HARD_LINK_DEPENDENCY){
			if(e.dest_id == v.id){
				Vertex& v1 = find_vertex(e.src_id);
				if(v1.pack_offset < 0){
					calculate_pack_offset(v1.id);
				}
			}
		}
	}


	for(auto& e : _edge_list){
		if(e.link_type == HARD_LINK_DEPENDENCY){
			if(e.src_id == v.id){
				Vertex& v2 = find_vertex(e.dest_id);
				if(v2.pack_offset < 0){
					if(v.pack_offset < 0){
						v.pack_offset = 0;
					}
					v2.pack_offset = v.pack_offset + e.distance;
					calculate_pack_offset(v2.id);
				}else{
					if(v.pack_offset < 0){
						v.pack_offset = v2.pack_offset - e.distance;
						if(v.pack_offset < 0){
							int off = v.pack_offset;
							for(auto& vv : _vertex_list){
								if(vv.pack_id == v.pack_id && vv.pack_offset>=0){
									vv.pack_offset += (-off);
								}
							}
							v.pack_offset = 0;
						}
					}else{
						if(v2.pack_offset != v.pack_offset + e.distance){
							cout << "ERROR! Conflict hard link graph!" << v.id << ", " <<v2.id << ":" << v.pack_offset << ", "<<v2.pack_offset << endl;
							exit(-1);
						}
					}
				}
			}
		}
		if(v.pack_offset < 0){
			v.pack_offset = 0;
		}
	}
}

void DependencyGraph::assign_packs(){
	int max_pack_id = 0;
	for(auto& v : _vertex_list){
		v.pack_id = max_pack_id;
		v.pack_offset = -1;
		max_pack_id++;
	}
	
	for(int i=0; i<_vertex_list.size(); i++){
		bool changed = false;
		for(auto& e: _edge_list){
			if(e.link_type == HARD_LINK_DEPENDENCY){
				Vertex& v1 = find_vertex(e.src_id);
				Vertex& v2 = find_vertex(e.dest_id);
				if(v1.pack_id < v2.pack_id){
					v2.pack_id = v1.pack_id;
					changed = true;
				}else if(v1.pack_id > v2.pack_id){
					v1.pack_id = v2.pack_id;
					changed = true;
				}
			}
		}
		if(!changed){
			break;
		}
	}
	
	for(auto& v : _vertex_list){
		calculate_pack_offset(v.id);
	}
	
	// Verify soft links inside pack
	for(auto& e : _edge_list){
		Vertex& v1 = find_vertex(e.src_id);
		Vertex& v2 = find_vertex(e.dest_id);
		if(e.link_type == SOFT_LINK_DEPENDENCY && v1.pack_id == v2.pack_id){
			if(v1.pack_offset >= v2.pack_offset){
				cout << "ERROR! Conflict soft links in pack." << endl;
				exit(-1);
			}
		}
	}
}

void DependencyGraph::schedule(){
	assign_packs();
	
	int min_end_time = 10000;
	vector<Vertex> scheduled_vertex_set_in;
	vector<Vertex> unscheduled_vertex_set_in;
	map<string, int> clock_in;
	vector<Vertex> solution_out;
	vector<vector<Vertex>> solution_list_out;
	unscheduled_vertex_set_in = _vertex_list;
	for(auto& v : unscheduled_vertex_set_in){
		for(auto& it : v.resource){
			if(clock_in.find(it.first) == clock_in.end()){
				clock_in[it.first] = 0;
			}
		}
		v.active=true;
	}
	
	try_schedule_one(scheduled_vertex_set_in, unscheduled_vertex_set_in, clock_in, solution_out, min_end_time, solution_list_out);
	
	if(solution_out.size()<=0){
		LOG(FATAL) << "Scheduling failed!";
	}
	
	for(auto& v : solution_out){
		Vertex& vv = find_vertex(v.id);
		vv.start = v.start;
	}
	
	for(int i=0; i<solution_list_out.size(); i++){
		int max_latency = 0;
		for(auto& v:solution_list_out[i]){
			int latency=0;
			for(auto r:v.resource){
				if(latency<v.start+r.second[1]){
					latency = v.start+r.second[1];
				}
			}
			if(max_latency < latency){
				max_latency = latency;
			}
		}
		cout << "solution " << i << ", latency = " << max_latency << endl;
	}
}

void DependencyGraph::try_schedule_one(vector<Vertex> scheduled_vertex_set_in, vector<Vertex>unscheduled_vertex_set_in, map<string, int> clock_in, vector<Vertex>& solution_out, int& min_end_time, vector<vector<Vertex>>& solution_list_out){


	// Early return if timing of current solution is worse than the known solution
	for(auto& it : clock_in){
		if(it.second >= min_end_time){
			solution_out={};
			return;
		}
	}
	
	// Return if solution is found
	if(unscheduled_vertex_set_in.size()<=0){
		int min_end_time_temp = 0;
		for(auto& it : clock_in){
			if(it.second > min_end_time_temp){
				min_end_time_temp = it.second;
			}
		}
		solution_out = scheduled_vertex_set_in;
		min_end_time = min_end_time_temp;
		solution_list_out.push_back(solution_out);
		return;
	}
	
	// Make supernodes for packs
	vector<Vertex> packs;
	map<int, bool> mask;
	for(auto& v : unscheduled_vertex_set_in){
		mask[v.id] = false;
	}
	
	for(auto& v : unscheduled_vertex_set_in){
		if(mask[v.id]){
			continue;
		}
		
		mask[v.id] = true;
		Vertex pack_item(v.pack_id, to_string(v.pack_id));
		pack_item.pack_id = v.pack_id;
		pack_item.pack_offset = 0;
		pack_item.active=true;
		if(!v.active){
			pack_item.active=false;
		}
		map<string, vector<int> > resource;
		for(auto& res : v.resource){
			if(resource.find(res.first) != resource.end()){
				if(resource[res.first][0] > res.second[0] + v.pack_offset){
					resource[res.first][0] = res.second[0] + v.pack_offset;
				}
				if(resource[res.first][1] < res.second[1] + v.pack_offset){
					resource[res.first][1] = res.second[1] + v.pack_offset;
				}
			}else{
				resource[res.first] = {res.second[0] + v.pack_offset, res.second[1] + v.pack_offset};
			}
		}
		pack_item.resource = resource;
		pack_item.children.push_back(v);
		for(auto& vv : unscheduled_vertex_set_in){
			if(mask[vv.id]){
				continue;
			}
			if(vv.pack_id == pack_item.pack_id){
				mask[vv.id] = true;
				if(!v.active){
					pack_item.active=false;
				}
				for(auto& res : vv.resource){
					auto it=pack_item.resource.find(res.first);
					if(pack_item.resource.find(res.first)!=pack_item.resource.end()){
						if(pack_item.resource[res.first][0] > res.second[0] + vv.pack_offset){
							pack_item.resource[res.first][0] = res.second[0] + vv.pack_offset;
						}
						if(pack_item.resource[res.first][1] < res.second[1] + vv.pack_offset){
							pack_item.resource[res.first][1] = res.second[1] + vv.pack_offset;
						}
					}else{
						pack_item.resource[res.first] = {res.second[0] + vv.pack_offset, res.second[1] + vv.pack_offset};
					}
				}
				pack_item.children.push_back(vv);
			}
		}
		packs.push_back(pack_item);
	}

	int i=0;
	for(int jj=0; jj<packs.size(); jj++){
		auto& pk=packs[jj];
		if(!pk.active){
			continue;
		}
		string str;
		for(auto& c : pk.children){
			str += (c.name + ",");
		}
		
		// Early return if at least one predecessor (with distance > 0) of p is not scheduled
		bool flag_predecessor_not_scheduled = false;
		for(auto& v : pk.children){
			for(auto& e : _edge_list){
				if(e.dest_id == v.id && e.link_type == SOFT_LINK_DEPENDENCY && e.distance>0){
					bool flag_pre_scheduled=false;
					for(auto& vv : scheduled_vertex_set_in){
						if(vv.id == e.src_id){
							flag_pre_scheduled = true;
							break;
						}
					}
					if(!flag_pre_scheduled){
						flag_predecessor_not_scheduled = true;
						break;
					}
				}
			}
			if(flag_predecessor_not_scheduled){
				break;
			}
		}
		
		if(flag_predecessor_not_scheduled){
			continue;
		}
		// Check mininal schedule time
		int min_schedule_time = 0;
		for(auto& v : pk.children){
			for(auto& e : _edge_list){
				Vertex& v1 = find_vertex(e.src_id);
				if(e.dest_id == v.id && e.link_type == SOFT_LINK_DEPENDENCY && v1.pack_id != v.pack_id){
					for(auto& vv : scheduled_vertex_set_in){
						if(vv.id == e.src_id){
							if((vv.start+e.distance+1-v.pack_offset) > min_schedule_time){
								min_schedule_time = (vv.start+e.distance+1-v.pack_offset);
							}
						}
					}
				}
			}
		}
		// Try schedule this pack
		Vertex v_out;
		map<string, int> c_out;
		schedule_one_vertex(pk, clock_in, min_schedule_time, v_out, c_out);

		vector<Vertex> new_unscheduled_vertex_set;
		vector<Vertex> new_scheduled_vertex_set = scheduled_vertex_set_in;
		for(auto& v : v_out.children){
			new_scheduled_vertex_set.push_back(v);
		}
		for(auto& v : unscheduled_vertex_set_in){
			bool flag_scheduled = false;
			for(auto& vv : v_out.children){
				if(vv.id == v.id){
					flag_scheduled = true;
					break;
				}
			}
			if(flag_scheduled){
				continue;
			}
			new_unscheduled_vertex_set.push_back(v);
		}
		// Check whether the schedule is valid or not
		bool flag_not_valid = false;
		for(auto& v : v_out.children){
			for(auto& e : _edge_list){
				if(e.link_type == SOFT_LINK_DEPENDENCY){
					if(e.src_id == v.id){
						for(auto& vv : scheduled_vertex_set_in){
							if(e.dest_id == vv.id){
								if(v.start+e.distance >= vv.start){
									flag_not_valid = true;
									break;
								}
							}
						}
					}else if(e.dest_id == v.id){
						for(auto& vv : scheduled_vertex_set_in){
							if(e.src_id == vv.id){
								if(vv.start+e.distance >= v.start){
									flag_not_valid = true;
									break;
								}
							}
						}
					}
				}
				if(flag_not_valid){
					break;
				}
			}
			if(flag_not_valid){
				break;
			}
		}
		if(flag_not_valid){
			continue;
		}
		for(auto& vv: new_unscheduled_vertex_set){
			vv.active=true;
		}
		for(int ii=0; ii<jj; ii++){
			auto& p1 = packs[ii];
			bool flag_find_relavant=false;
			for(auto& r : p1.resource){
				if(pk.resource.find(r.first)!=pk.resource.end()){
					flag_find_relavant = true;
				}
			}
			if(flag_find_relavant){
				continue;
			}
			
			for(auto& v1: p1.children){
				for(auto& v2: pk.children){
					for(auto& e1 : _edge_list){
						if((e1.src_id==v1.id && e1.dest_id==v2.id) || (e1.dest_id==v1.id && e1.src_id==v2.id)){
							flag_find_relavant=true;
							break;
						}
					}
					if(flag_find_relavant){
						break;
					}
				}
				if(flag_find_relavant){
					break;
				}
			}
			if(flag_find_relavant){
				continue;
			}
			
			for(auto& v1: p1.children){
				for(auto& vv: new_unscheduled_vertex_set){
					if(vv.id == v1.id){
						vv.active=false;
					}
				}
			}
		}
		
		// Search new space based on this scheduling
		vector<Vertex> one_solution;
		try_schedule_one(new_scheduled_vertex_set, new_unscheduled_vertex_set, c_out, one_solution, min_end_time, solution_list_out);
		if(one_solution.size()>0){
			solution_out = one_solution;
			// FIXME: Directly add return to disable back tracking
			return;
		}
	}
}

void DependencyGraph::schedule_one_vertex(Vertex v_in, map<string, int> c_in, int min_schedule_time, Vertex& v_out, map<string, int>& c_out){
	v_out = v_in;
	c_out = c_in;
	
	int max_clk = 0;
	map<string, vector<int> > rs_clk_map;
	for(auto& it : v_in.resource){
		if(c_in[it.first]> max_clk){
			max_clk = c_in[it.first];
		}
	}
	
	for(auto& it : v_in.resource){
		rs_clk_map[it.first] = {c_in[it.first] - max_clk, it.second[0], it.second[1]};
	}
	
	int min_space = 10000;
	for(auto& it : rs_clk_map){
		if(min_space > (it.second[1] - it.second[0])){
			min_space = it.second[1] - it.second[0];
		}
	}
	
	if(max_clk-min_space >= min_schedule_time){
		v_out.start = max_clk - min_space;
	}else{
		v_out.start = min_schedule_time;
	}
	
	for(auto& it : c_in){
		if(v_out.resource.find(it.first)!=v_out.resource.end()){
			c_out[it.first] = v_out.start + v_out.resource[it.first][1] + 1;
		}else{
			c_out[it.first] = it.second;
		}
	}
	
	for(auto& c : v_out.children){
		c.start = v_out.start + c.pack_offset;
	}
}

}
}
