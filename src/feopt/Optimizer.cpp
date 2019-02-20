#include "Optimizer.hpp"

namespace vesyla
{
namespace feopt
{
Optimizer::Optimizer()
{
}
Optimizer::~Optimizer()
{
}
void Optimizer::optimize(cidfg::CidfgGraph &g_)
{
	gen_script();

	CleanEngine ec;

	ExprSimpEngine e0;
	e0.transform(g_);
	to_dot_graph(g_, 0);

	SrcConvEngine e1;
	e1.transform(g_);
	ec.transform(g_);
	to_dot_graph(g_, 1);

	RwiMergeEngine e2;
	e2.transform(g_);
	ec.transform(g_);
	to_dot_graph(g_, 2);

	BindEngine e3;
	e3.transform(g_);
	ec.transform(g_);
	to_dot_graph(g_, 3);

	DependencyAnalyzeEngine e4;
	e4.transform(g_);
	ec.transform(g_);
	to_dot_graph(g_, 4);
}

void Optimizer::to_dot_graph(cidfg::CidfgGraph &g_, int stage_)
{
	vesyla::util::GlobalVar glv;
	string path;
	string input_file_name;
	CHECK(glv.gets("$OUTPUT_DIR", path));
	path = path + "feopt/";
	mkdir(path.c_str(), 0755);
	CHECK(glv.gets("input_file_name", input_file_name));
	string path_dot;
	path_dot = path + input_file_name + "_e" + to_string(stage_) + ".dot";
	ofstream ofs0(path_dot, ofstream::out);
	ofs0 << g_.generate_dot_graph();
	ofs0.close();
}

void Optimizer::gen_script()
{
	vesyla::util::GlobalVar glv;
	string path;
	CHECK(glv.gets("$OUTPUT_DIR", path));
	path = path + "feopt/";
	mkdir(path.c_str(), 0755);
	string path_dot;
	path_dot = path + "convert.sh";
	ofstream ofs0(path_dot, ofstream::out);
	cidfg::ScriptGenerator sg;
	ofs0 << sg.generate();
	ofs0.close();
	chmod(path_dot.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
}

} // namespace feopt
} // namespace vesyla