#include "main.hpp"

int main(int argc, char* argv[]){
	
	// Argument parsing
	string path_matlab;
	string path_fabric;
	options_description desc("Options"); 
	desc.add_options()
	("help,h", "Print help messages")
	("matlab,m", value<string>(&path_matlab)->required(), "The result file from matlab simulation")
	("fabric,f", value<string>(&path_fabric)->required(), "The result file from fabric simulation");
	
	variables_map vm;
	try{
		store(parse_command_line(argc, argv, desc), vm);
		if(vm.count("help")){
			cout	<< "Vesyla verification tool" << endl 
						<< desc << endl; 
			return 0; 
		}
		notify(vm);
	}catch(error& e){
		cerr << endl;
		cerr << "ERROR:" << e.what() << endl;
		cerr << endl;
		cerr << desc << endl;
		return -1;
	}
	
	
	// Compare
	Comparator cmp(path_matlab, path_fabric);
	
	if(cmp.compare()){
	cout << "\n---------------------------------------------------------------------\n";
		cout<<"<<PASS>>";
		cout << "\n---------------------------------------------------------------------\n";
		return 0;
	}else{
	cout << "\n---------------------------------------------------------------------\n";
		cout<<"<<FAIL>>";
		cout << "\n---------------------------------------------------------------------\n";
		return -1;
	}
	return 0;
}
