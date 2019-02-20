#include "Comparator.hpp"

namespace vesyla{
namespace verify{

Comparator::Comparator(const string& path_matlab, const string& path_fabric){
	_matlab_tokens = get_tokens(path_matlab);
	_fabric_tokens = get_tokens(path_fabric);
}

bool Comparator::compare(){
	if(_matlab_tokens.size() != _fabric_tokens.size()){
		cerr << "ERROR:" << "Token counts don't match! "
					<< _matlab_tokens.size() << " != " << _fabric_tokens.size() << endl;
		return false;
	}
	
	bool correct = true;
	for(auto it=_fabric_tokens.begin(); it!=_fabric_tokens.end(); it++){
		auto it2 = _matlab_tokens.find(it->first);
		if(it2==_matlab_tokens.end()){
			cerr << "ERROR:" << "Token "<< it->first <<" is not exist! " << endl;
			correct=false;
			continue;
		}
		if(it2->second!=it->second){
			cerr << "ERROR:" << "Token "<< it->first <<" mismatch! " << endl;
			correct=false;
			continue;
		}
	}
	return correct;
}

map<string, vector<float>> Comparator::get_tokens(const string& path){
	map<string, vector<float>> m;
	
	regex e("([^\\(]+)\\(([^\\)]+)\\)\\s*=\\s*([-eE\\d\\.\\s]*)");
	char line[1024];
	
	//boost::filesystem::basic_ifstream<string> ifs(path);
	std::ifstream ifs(path);
	if(!ifs){
		cerr << "ERROR:" << "can't open file " << path << endl;
		return m;
	}
	while (ifs.getline(line, 1024)){
		string lineStr(line);
		if(lineStr.size()>0){
			match_results<string::const_iterator> result;
			if(regex_match(lineStr, result, e, match_default|match_partial)==0){
				continue;
			}
			if(!result[0].matched){
				continue;
			}
			string f1 = result[1];
			string f2 = to_string(stoi(result[2]));
			float f3 = stof(result[3]);
			
			string key = f1+"_"+f2;
			float val = f3;
			
			if (m.find(key) == m.end()){
				vector<float> v={val};
				m[key] = v;
			}else{
				m[key].push_back(val);
			}
		}
	}
	return m;
}

}
}
