#ifndef __VESYLA_CODE_GEN_INSTR_GENERATOR_HPP__
#define __VESYLA_CODE_GEN_INSTR_GENERATOR_HPP__

#include "util/Common.hpp"
#include "VIR/VIRIncludeAll.hpp"
#include "BIR/BIRIncludeAll.hpp"
#include "BranchManager.hpp"
#include "SwbManager.hpp"
#include "PrimitiveFuncLib.hpp"
using json = nlohmann::json;

using namespace BIR;
using namespace VIR;
using namespace BIR::BIREnumerations;
using namespace VIR::VirEnumerations;

namespace vesyla{
namespace codegen{

typedef struct
	{
		bool operator()(const VIR::ForStatement * a, const VIR::ForStatement * b) const;
	} CompareMapElements;
struct MappedInstruction
	{
		VIR::Coordinate cellCoord;
		BIR::Instruction * instruction;

		MappedInstruction(const VIR::Coordinate & cellCoord_, BIR::Instruction * inst_) :
			cellCoord(cellCoord_), instruction(inst_) {}
	};
typedef map<VIR::ForStatement *, int, CompareMapElements> LoopValuesMap;

class InstrGenerator{
private:

	BranchManager1 _branch_manager;
	PrimitiveFuncLib _primitive_func_lib;
	SwbManager _swb_manager;

public:
	JumpInstruction* createJumpInstruction(int statementNo_, VIR::Coordinate& coord_, LoopValuesMap * loopValues_);
	map<string, BIR::LoopHeaderInstruction*> createLoopHeaderInstruction(ForStatement * forStatement_, LoopValuesMap * loopValues_, json& j_, string path_);
	void createLoopTailInstruction(ForStatement * forStatement_, LoopValuesMap * loopValues_, json& j_, string path_);
	void createDpuInstruction(BIR::DPUInstruction * dpuInst_, int statementNo_, string unrolledStatementNo_, VIR::DPUPragma * dpuPragma_, LoopValuesMap * loopValues_, const Coordinate & dpuCoord_, int repetition_, bool fixedPointMode_);
	BIR::WaitInstruction * createDummyWaitInstruction(int statementNo_, LoopValuesMap * loopValues_, VIR::Coordinate & coord_);
	BranchInstruction* createBranchInstruction(VIR::BinaryExpression * binaryExpression, int statementNo_, string unrolledStatementNo_, const VIR::Coordinate & coord_, LoopValuesMap * loopValues_);
	BIR::RouteInstruction * createRouteInstruction(int statementNo_, string unrolledStatementNo_, const VIR::Coordinate & memoryCoord_, const VIR::Coordinate & regFileCoord_, LoopValuesMap * loopValues_, bool isMemToRegTrans_, const string variableName_);
	SRAMInstruction * createSramInstruction(VIR::SliceName * sliceName_, int statementNo_, string unrolledStatementNo_,const VIR::Coordinate & memoryCoord_, const VIR::Coordinate & regFileCoord_, LoopValuesMap * loopValues_, bool isMemToRegTrans_, IndexInfo * indexInfo_, int memoryStartAddr_, const string variableName_, BIR::RefiInstruction * correspondingRefiInst_, BIR::RouteInstruction * correspondingRouteInst_);
	BIR::SWBInstruction * createSwbInstruction(int statementNo_, string unrolledStatementNo_, const string & variableName_, LoopValuesMap * loopValues_, vector<BIR::SWBInstruction *> & swbInstructions_, const VIR::Coordinate & referenceCoord_, const BIR::ComponentInfo & srcComponentInfo_, const BIR::ComponentInfo & destComponentInfo_);
	void createRaccuInstruction(int statementNo_, BIR::BIREnumerations::RACCUMode raccuMode_, int operand1_, bool isOp1Static_, int operand2_, bool isOp2Static_, int & resultAddress_, const VIR::Coordinate & cellCoord_, const VIR::Coordinate & refCoord_, LoopValuesMap * loopValues_, BIR::Instruction * dependentInst_, int instInsertLocation_ = -1, VIR::ForStatement * forStatement_ = 0);
};
	BIR::RefiInstruction * createRefiInstruction(int statementNo_, int twinStatementNo_, string unrolledStatementNo_, const string & variableName_, BIR::BIREnumerations::AddressMode addressMode_, BIR::BIREnumerations::PortMode portMode_, int numberOfAddress_, int stepValue_, int numberOfRepetition_, int repetitionOffset_, int reverse_bits_, bool is_reverse_bits_static_, bool isDimarchMode_, bool isInResSharingRegion_, BIR::DPUInstruction * correspondingDpuInst_, const string & pureVariableName_);
	void createRfileInstruction(VIR::SliceName * sliceName_, LoopValuesMap * loopValues_, VIR::ReferencePragma * regFilePragma_, int statementNo_, string unrolledStatementNo_, vector <MappedInstruction> & mappedRefiInsts_, int posIndex_, bool isMemToRegTrans_);
	BIR::RouteInstruction * createRouteInstruction(int statementNo_, string unrolledStatementNo_, const VIR::Coordinate & memoryCoord_, const VIR::Coordinate & regFileCoord_, LoopValuesMap * loopValues_, bool isMemToRegTrans_, const string variableName_);
	BIR::SRAMInstruction * createSramInstruction(VIR::SliceName * sliceName_, int statementNo_, string unrolledStatementNo_, const VIR::Coordinate & memoryCoord_, const VIR::Coordinate & regFileCoord_, LoopValuesMap * loopValues_, bool isMemToRegTrans_, VIR::IndexInfo * indexInfo_, int memoryStartAddr_, const string variableName_, BIR::RefiInstruction * correspondingRefiInst_, BIR::RouteInstruction * correspondingRouteInst_);
	BIR::SWBInstruction * createSwbInstruction(int statementNo_, string unrolledStatementNo_, const string & variableName_, LoopValuesMap * loopValues_, vector<BIR::SWBInstruction *> & swbInstructions_, const VIR::Coordinate & referenceCoord_, const BIR::ComponentInfo & srcComponentInfo_, const BIR::ComponentInfo & destComponentInfo_);
	
		bool calculateDynamicStartAddress(int & startAddress_, VIR::IndexInfo * indexInfo_, int statementNo_, BIR::Instruction * dependentInst_, LoopValuesMap * loopValues_, const VIR::Coordinate & referenceCoord_, const VIR::Coordinate & regFileCoord_, const string & indexVariableName_, bool isForMemory_);


}
}

#endif
