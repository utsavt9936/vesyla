
#include "MemoryManager.hpp"
#include "../VIR/VIRIncludeAll.hpp"
#include "../BIR/BIRIncludeAll.hpp"

using namespace VIR;
using namespace VIR::VirEnumerations;

using namespace BIR;
using namespace BIR::BIREnumerations;

// Initializing the singleton
MEMORY_PLATE * MEMORY_PLATE::_singletonInst = new MemoryManager();

// Getting singleton instance
MEMORY_PLATE* MEMORY_PLATE::inst()
{
	return _singletonInst;
}

void MEMORY_PLATE::changeCurrentLibrary(int libraryId_)
{
	_currLibraryId = libraryId_;

	_currObjectVector = _objectsLibrary[libraryId_];
}

//! Performing garbage collection for the remaining objects
void MEMORY_PLATE::collectGarbage()
{
	for (map<int, ObjectVector*>::iterator iter = _objectsLibrary.begin(); iter != _objectsLibrary.end(); ++iter)
	{
		ObjectVector *objectVector = iter->second;

		for (int i = 0; i < (int)objectVector->size(); ++i)
			delete objectVector->at(i);

		delete objectVector;
	}

	for (int i = 0; i < (int)_birObjectVector.size(); ++i)
		delete _birObjectVector.at(i);

	_birObjectVector.clear();
}

//! Creating a binary expression
VIR::BinaryExpression * MEMORY_PLATE::createBinaryExpression(BinaryOperatorType opType_, Expression * leftOp_, Expression * rightOp_)
{
	BinaryExpression *binaryExpression = CREATE_OBJECT_INSIDE(BinaryExpression);

	binaryExpression->operatorType(opType_);
	binaryExpression->leftOperand(leftOp_);
	binaryExpression->rightOperand(rightOp_);

	return binaryExpression;
}

// Creating a floating point expression
VIR::FloatingPoint * MemorySpace::MemoryManager::createFloatingPoint(float value_)
{
	FloatingPoint * floatingPoint = CREATE_OBJECT_INSIDE(FloatingPoint);

	floatingPoint->value = value_;

	return floatingPoint;
}

// Creating a special kind of range expression to show the total possible range (-1 : 1 : -1)
VIR::RangeExpression * MEMORY_PLATE::createFullRangeExpression()
{
    RangeExpression *rangeExpression = CREATE_OBJECT_INSIDE(RangeExpression);

    rangeExpression->increment(createInteger(1));
    rangeExpression->begin(createInteger(-1));
    rangeExpression->end(createInteger(-1));

	return rangeExpression;
}

// Creating an identifier object with the given name
VIR::Identifier * MEMORY_PLATE::createIdentifier(string name_)
{
	Identifier * identifier = CREATE_OBJECT_INSIDE(Identifier);

	identifier->name(name_);

	return identifier;
}

// Creating an integer expression
VIR::Integer * MEMORY_PLATE::createInteger(int value_)
{
	Integer *integer = CREATE_OBJECT_INSIDE(Integer);

	integer->value = value_;

	return integer;
}

// This method creates a LOOP_HEADER instruction.
BIR::LoopHeaderInstruction * MEMORY_PLATE::createLoopHeaderInstruction(int statementNo_, string unrolledStatementNo_, int loopId, bool isStatic_, int startValue_, int iterationNumber_)
{
	LoopHeaderInstruction * loopHeaderInst = CREATE_OBJECT_B(LoopHeaderInstruction);

	loopHeaderInst->statementNo = statementNo_;
	loopHeaderInst->unrolledStatementNo = unrolledStatementNo_;
	loopHeaderInst->loopId = loopId;
	loopHeaderInst->isStatic = isStatic_;
	loopHeaderInst->startValue = startValue_;
    loopHeaderInst->iterationNumber = iterationNumber_;
	loopHeaderInst->correspondingLoopTailInst = 0;
	loopHeaderInst->upperLoop = 0;

	return loopHeaderInst;
}

// This method creates a LOOP_TAIL instruction.
BIR::LoopTailInstruction * MEMORY_PLATE::createLoopTailInstruction(int statementNo_, string unrolledStatementNo_, int loopId_, int gotoPC_, int stepValue_)
{
	LoopTailInstruction * loopTailInst = CREATE_OBJECT_B(LoopTailInstruction);

	loopTailInst->statementNo = statementNo_;
    loopTailInst->unrolledStatementNo = unrolledStatementNo_;
    loopTailInst->loopId = loopId_;
    loopTailInst->gotoPC = gotoPC_;
    loopTailInst->stepValue = stepValue_;

	return loopTailInst;
}

void MEMORY_PLATE::createNewLibrary()
{
	static int uniqueId = -1;

	_currObjectVector = new ObjectVector();

	_currLibraryId = ++uniqueId;

	_objectsLibrary[uniqueId] = _currObjectVector;

}

//! Creating an object according to the given kind
VIRBase* MEMORY_PLATE::createObject(KindType kind_)
{
	VIRBase *object;

	switch (kind_)
	{
		case ktAddressObjectDeclaration:object = new AddressObjectDeclaration();break;
		case ktAddressPragma:			object = new AddressPragma();			break;
		case ktArray:					object = new Array();					break;
		case ktAssignmentStatement:		object = new AssignmentStatement(); 	break;
		case ktBinaryExpression:		object = new BinaryExpression();		break;
		case ktBlockPragma:				object = new BlockPragma();				break;
		case ktComplex:					object = new Complex();					break;
		case ktDebugStatement:			object = new DebugStatement();			break;
		case ktDPUChainPragma:			object = new DPUChainPragma();			break;
		case ktDPUPragma:				object = new DPUPragma();				break;
		case ktFloatingPoint:			object = new FloatingPoint();			break;
		case ktForStatement:			object = new ForStatement();			break;
		case ktFunctionDeclaration:		object = new FunctionDeclaration();		break;
		case ktFunctionCall:			object = new FunctionCall();			break;
		case ktIdentifier:				object = new Identifier();				break;
		case ktIndexInfo:				object = new IndexInfo();				break;
		case ktIfStatement:				object = new IfStatement();				break;
		case ktIfThenElseStatement:		object = new IfThenElseStatement();		break;
		case ktInteger:					object = new Integer();					break;
		case ktLoopObjectDeclaration:	object = new LoopObjectDeclaration();	break;
		case ktMainProgram:				object = new MainProgram();				break;
		case ktObjectDeclaration:		object = new ObjectDeclaration();		break;
		case ktParenthesizedExpression:	object = new ParenthesizedExpression();	break;
		case ktPragmaExpression:		object = new PragmaExpression();		break;
		case ktPragmaStatement:			object = new PragmaStatement();			break;
		case ktPrimitiveFunctionCall:	object = new PrimitiveFunctionCall();	break;
		case ktRaccuPragma:				object = new RaccuPragma();				break;
		case ktRangeExpression:			object = new RangeExpression();			break;
		case ktSliceName:				object = new SliceName();				break;
		case ktStoragePragma:			object = new StoragePragma();			break;
		case ktStringLiteral:			object = new StringLiteral();			break;
		case ktTempVarPragma:			object = new TempVarPragma();			break;
		case ktUnaryExpression:			object = new UnaryExpression();			break;
		case ktFunctionCallStatement: object = new FunctionCallStatement(); break;
	}

	object->_kind = kind_;
	object->_id = _globalId++;
	object->_lineNumber = 0;

	// keeping objects for future garbage collection
	_currObjectVector->push_back(object);

	return object;
}

BIR::BIRBase * MEMORY_PLATE::createObjectB(BIRKindType kind_)
{
	BIRBase * object;

	switch (kind_)
	{
		//case bktAGU:					object = new AGU();						break;
		case bktBranchInstruction:		object = new BranchInstruction();		break;
		case bktDPU:					object = new DPU();						break;
		//case bktDRRACell:				object = new DRRACell();				break;
		case bktDPUInstruction:			object = new DPUInstruction();			break;
		case bktLoopHeaderInstruction:	object = new LoopHeaderInstruction();	break;
		case bktLoopTailInstruction:	object = new LoopTailInstruction(); 	break;
		case bktJumpInstruction:		object = new JumpInstruction();			break;
		//case bktRACCU:				object = new RACCU();					break;
		case bktRACCUInstruction:		object = new RACCUInstruction();		break;
		case bktRefiInstruction:		object = new RefiInstruction();			break;
		case bktRefi1Instruction:		object = new Refi1Instruction();		break;
		case bktRefi2Instruction:		object = new Refi2Instruction();		break;
		case bktRefi3Instruction:		object = new Refi3Instruction();		break;
		case bktRegister:				object = new Register();				break;
		//case bktRegFile:				object = new RegFile();					break;
		case bktRFILEInstruction:		object = new RFILEInstruction();		break;
		case bktRouteInstruction:		object = new RouteInstruction();		break;
		//case bktSequencer:			object = new Sequencer();				break;
		case bktSRAMInstruction:		object = new SRAMInstruction();			break;
		case bktSWBInstruction:			object = new SWBInstruction();			break;
		case bktSwitchBox:				object = new SwitchBox();				break;
		case bktWaitInstruction:		object = new WaitInstruction();			break;
	}

	object->_kind = kind_;
	object->_id = _globalIdB++;

	// keeping objects for future garbage collection
	_birObjectVector.push_back(object);

	return object;
}


VIR::RangeExpression * MEMORY_PLATE::createRangeExpression(int begin_, int increment_, int end_)
{
	RangeExpression *rangeExpression = CREATE_OBJECT_INSIDE(RangeExpression);

	rangeExpression->begin(createInteger(begin_));
	rangeExpression->increment(createInteger(increment_));
	rangeExpression->end(createInteger(end_));

	return rangeExpression;
}

VIR::UnaryExpression * MEMORY_PLATE::createUnaryExpression(UnaryOperatorType opType_, Expression *operand_)
{
	UnaryExpression *unaryExpression = CREATE_OBJECT_INSIDE(UnaryExpression);

	unaryExpression->operatorType(opType_);
	unaryExpression->operand(operand_);

	return unaryExpression;
}

// This method creates a wait instruction.
// Note that because the wait instruction itself takes one clock cycle, 
// so the numberOfCycles field of the instruction is set to one less than the given waitCycle.
BIR::WaitInstruction * MemorySpace::MemoryManager::createWaitInstruction(int statementNo_, string unrolledStatementNo_, int waitCycle_, bool isStatic_, int scheduledCycle_)
{
	WaitInstruction * waitInstruction = CREATE_OBJECT_B(WaitInstruction);

	waitInstruction->statementNo = statementNo_;
	waitInstruction->unrolledStatementNo = unrolledStatementNo_;
	waitInstruction->numberOfCycles(waitCycle_ - 1, isStatic_); // -1 because the wait instruction itself will take 1 clock cycle.
	waitInstruction->minScheduledClkCycle = scheduledCycle_;
	waitInstruction->maxScheduledClkCycle = scheduledCycle_ + waitInstruction->numberOfCycles.value;

	return waitInstruction;
}

int MemorySpace::MemoryManager::currLibraryId() const
{
	return _currLibraryId;
}

void MemorySpace::MemoryManager::deleteLibrary(int libraryId_)
{
	ObjectVector *objectVector = _objectsLibrary[libraryId_];

	for (int i = 0; i < (int)objectVector->size(); ++i)
		delete objectVector->at(i);

	delete objectVector;

	_objectsLibrary.erase(libraryId_);
}

