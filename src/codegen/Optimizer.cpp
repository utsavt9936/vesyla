#include "Optimizer.hpp"

namespace vesyla
{
namespace codegen
{
Optimizer::Optimizer()
{
}
Optimizer::~Optimizer()
{
}
schedule::Descriptor Optimizer::optimize(cidfg::CidfgGraph &g_)
{
	gen_script();

	vesyla::codegen::IteratorReplacementEngine e0;
	e0.transform(g_);
	to_dot_graph(g_, 0);
	vesyla::codegen::MulDivTransEngine e1;
	e1.transform(g_);
	to_dot_graph(g_, 1);
	vesyla::codegen::RootVertexConverter rvc;
	rvc.convert(g_);
	to_dot_graph(g_, 2);
	vesyla::codegen::ComputationVertexConverter cvc;
	cvc.convert(g_);
	to_dot_graph(g_, 3);
	vesyla::codegen::LoopVertexConverter lvc;
	lvc.convert(g_);
	to_dot_graph(g_, 4);
	vesyla::codegen::BranchVertexConverter bvc;
	bvc.convert(g_);
	to_dot_graph(g_, 5);
	vesyla::codegen::GeneralHierarchicalVertexConverter ghvc;
	ghvc.convert(g_);
	to_dot_graph(g_, 6);
	vesyla::codegen::IndexVertexConverter ivc;
	ivc.convert(g_);
	to_dot_graph(g_, 7);
	vesyla::codegen::RouteEngine e8;
	e8.transform(g_);
	to_dot_graph(g_, 8);
	vesyla::codegen::SwbRearrangeEngine e9;
	e9.transform(g_);
	to_dot_graph(g_, 9);
	vesyla::codegen::CleanConverter cleaner;
	cleaner.convert(g_);
	to_dot_graph(g_, 10);
	vesyla::codegen::DescriptorGenerator dg;
	schedule::Descriptor d = dg.generate(g_);
	to_dot_graph(d, 101);
	return d;
}

void Optimizer::to_dot_graph(cidfg::CidfgGraph &g_, int stage_)
{
	vesyla::util::GlobalVar glv;
	string path;
	string input_file_name;
	CHECK(glv.gets("$OUTPUT_DIR", path));
	path = path + "codegen/";
	mkdir(path.c_str(), 0755);
	CHECK(glv.gets("input_file_name", input_file_name));
	string path_dot;
	path_dot = path + input_file_name + "_e" + to_string(stage_) + ".dot";
	ofstream ofs0(path_dot, ofstream::out);
	ofs0 << g_.generate_dot_graph();
	ofs0.close();
}

void Optimizer::to_dot_graph(schedule::Descriptor &d_, int stage_)
{
	vesyla::util::GlobalVar glv;
	string path;
	string input_file_name;
	CHECK(glv.gets("$OUTPUT_DIR", path));
	path = path + "codegen/";
	mkdir(path.c_str(), 0755);
	CHECK(glv.gets("input_file_name", input_file_name));
	string path_dot;
	path_dot = path + input_file_name + "_e" + to_string(stage_) + ".dot";
	ofstream ofs0(path_dot, ofstream::out);
	ofs0 << d_.generate_dot_graph();
	ofs0.close();
}

void Optimizer::gen_script()
{
	vesyla::util::GlobalVar glv;
	string path;
	CHECK(glv.gets("$OUTPUT_DIR", path));
	path = path + "codegen/";
	mkdir(path.c_str(), 0755);
	string path_dot;
	path_dot = path + "convert.sh";
	ofstream ofs0(path_dot, ofstream::out);
	cidfg::ScriptGenerator sg;
	ofs0 << sg.generate();
	ofs0.close();
	chmod(path_dot.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
}

} // namespace codegen
} // namespace vesyla