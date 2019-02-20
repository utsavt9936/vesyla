#ifndef __VESYLA_CODE_GEN_GENERATOR_HPP__
#define __VESYLA_CODE_GEN_GENERATOR_HPP__

#include "util/Common.hpp"
#include "VIR/VIRIncludeAll.hpp"
#include "BIR/BIRIncludeAll.hpp"
#include "InstrGenerator.hpp"
using json = nlohmann::json;
#include "schedule/Descriptor.hpp"
#include "SramAddressTransformer.hpp"
#include "RaccuVarManager.hpp"

namespace vesyla
{
namespace codegen
{

typedef map<int, VIR::Coordinate> CoordinateMap;

class Generator
{
private:
	bool _isNonConstantLoopRegion;
	VIR::ForStatement *_currLoop;
	InstrGenerator _ig;
	BranchManager1 _branch_manager;
	SwbManager _swb_manager;

	CoordinateMap _allUtilizedCells;
	CoordinateMap _allUtilizedDimarchCells;
	BIR::DRRACluster *_drraCluster;
	RaccuVarManager _raccu_var_manager;

public:
	Generator(CoordinateMap allUtilizedCells_, CoordinateMap allUtilizedDimarchCells_, BIR::DRRACluster *drraCluster_) : _allUtilizedCells(allUtilizedCells_), _allUtilizedDimarchCells(allUtilizedDimarchCells_), _drraCluster(drraCluster_), _isNonConstantLoopRegion(false) {}
	// void createInstructions(vector<Statement *> *statements_, json &j_, string path_);
	// void createInstructionsForArithmeticStatement(VIR::AssignmentStatement *assignStatement_, LoopValuesMap *loopValues_, json &j_, string path_);
	// void createInstructionsForAVariable(VIR::SliceName *sliceName_, LoopValuesMap *loopValues_, VIR::ReferencePragma *referencePragma_, int statementNo_, std::string unrolledStatementNo_, vector<MappedInstruction> &mappedRefiInsts_, BIR::DPUInstruction *dpuInst_, int dpuPosIndex_, bool isInput_, int operandOrderNo_, int twinStatementNo_, bool isForMemoryTransfer_, int reverse_bits_, bool fft);
	// void createInstructionsForIndirectAddress(VIR::SliceName *sliceName_, LoopValuesMap *loopValues_, VIR::ReferencePragma *referencePragma_, int statementNo_, std::string unrolledStatementNo_, vector<MappedInstruction> &mappedRefiInsts_);
	// void createInstructionsForMemoryTransfer(VIR::AssignmentStatement *assignStatement_, LoopValuesMap *loopValues_, json &j_, string path_);
	// void createInstructionsForRaccuVariable(VIR::AssignmentStatement *assignStatement_, LoopValuesMap *loopValues_, json &j_, string path_);
	// void createInstructionsForRegisterTransfer(VIR::AssignmentStatement *assignStatement_, LoopValuesMap *loopValues_, json &j_, string path_);
	// void createInstructionsForIfCondition(IfStatement *ifStatement_, LoopValuesMap *loopValues_, json &j_, string path_);

	void create_instr_for_memory_transfer(VIR::AssignmentStatement *statement_, schedule::Descriptor &d_, string path_, int child_group_ = 0);
	BIR::RouteInstruction *create_route_instr(int statementNo_, const VIR::Coordinate &memoryCoord_, const VIR::Coordinate &regFileCoord_, bool isMemToRegTrans_, const string variableName_);
	int reserve_raccu_var(int statementNo_, VIR::AddressFunction af_, VIR::Coordinate coord_);
	SRAMInstruction *create_sram_instr(VIR::SliceName *sliceName_, int statementNo_, const VIR::Coordinate &memoryCoord_, const VIR::Coordinate &regFileCoord_, bool isMemToRegTrans_, int memoryStartAddr_, const string variableName_);
	RACCUInstruction *create_raccu_instr(int statementNo_, BIR::BIREnumerations::RACCUMode raccuMode_, int operand1_, bool isOp1Static_, int operand2_, bool isOp2Static_, int resultAddress_);
};

} // namespace codegen
} // namespace vesyla

#endif
