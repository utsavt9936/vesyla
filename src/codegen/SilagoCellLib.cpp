#include "SilagoCellLib.hpp"

namespace vesyla{
namespace codegen{

void SilagoCellLib::load(const string path){
	using boost::property_tree::ptree;
	ptree pt;
	read_xml(path, pt);
	
	for(ptree::value_type &v : pt.get_child("SilagoCells")){
		if(v.first=="cell"){
			string cell_name = v.second.get<string>("<xmlattr>.name", "");
			CellConfig cc;
			cc.height = v.second.get<int>("<xmlattr>.height", -1);
			cc.width = v.second.get<int>("<xmlattr>.width", -1);
			cc.type = v.second.get<int>("<xmlattr>.type", -1);
			_silago_cell_map[cell_name] = cc;
		}
	}
}

int SilagoCellLib::get_height(const string name){
	auto it = _silago_cell_map.find(name);
	if(it==_silago_cell_map.end()){
		return -1;
	}
	return it->second.height;
}

int SilagoCellLib::get_width(const string name){
	auto it = _silago_cell_map.find(name);
	if(it==_silago_cell_map.end()){
		return -1;
	}
	return it->second.width;
}

int SilagoCellLib::get_type(const string name){
	auto it = _silago_cell_map.find(name);
	if(it==_silago_cell_map.end()){
		return -1;
	}
	return it->second.type;
}

}
}
