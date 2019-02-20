
#ifndef __MemoryManager_H__
#define __MemoryManager_H__

#include <vector>
#include <map>
#include "util/Common.hpp"
#include "VIR/KindType.hpp"
#include "VIR/BinaryOperatorType.hpp"
#include "VIR/UnaryOperatorType.hpp"
#include "BIR/BIRKindType.hpp"
#include "VIR/VIRIncludeAll.hpp"
#include "BIR/BIRIncludeAll.hpp"

#include <iostream>

using std::map;
using std::vector;

// 'B' in all variables and methods stands for BIR objects

namespace MemorySpace
{

#define MEMORY_PLATE MemorySpace::MemoryManager
#define CHANGE_CURRENT_LIBRARY(id) MEMORY_PLATE::inst()->changeCurrentLibrary(id)
#define CREATE_BINARY_EXPR(opType, leftOp, rightOp) MEMORY_PLATE::inst()->createBinaryExpression(opType, leftOp, rightOp)
#define CREATE_FLOATING_POINT(value) MEMORY_PLATE::inst()->createFloatingPoint(value)
#define CREATE_FULL_RANGE_EXPRESSION MEMORY_PLATE::inst()->createFullRangeExpression();
#define CREATE_IDENTIFIER(name) MEMORY_PLATE::inst()->createIdentifier(name)
#define CREATE_INTEGER(value) MEMORY_PLATE::inst()->createInteger(value)
#define CREATE_NEW_LIBRARY MEMORY_PLATE::inst()->createNewLibrary()
#define CREATE_OBJECT(castType) (castType *)MEMORY_PLATE::inst()->createObject(kt##castType)
#define CREATE_OBJECT_B(castType) (castType *)MEMORY_PLATE::inst()->createObjectB(bkt##castType)
#define CREATE_RANGE_EXPRESSION(begin, increment, end) MEMORY_PLATE::inst()->createRangeExpression(begin, increment, end)
#define CREATE_UNARY_EXPR(opType, operand) MEMORY_PLATE::inst()->createUnaryExpression(opType, operand)
#define CURR_LIBRARY_ID MEMORY_PLATE::inst()->currLibraryId()
#define DELETE_LIBRARY(id) MEMORY_PLATE::inst()->deleteLibrary(id)
#define GarbageCollector MEMORY_PLATE::inst()->collectGarbage()
#define CREATE_LOOP_HEADER_INST(stNo, unrolledStNo, loopId, isStatic, startValue, iterNo) MEMORY_PLATE::inst()->createLoopHeaderInstruction(stNo, unrolledStNo, loopId, isStatic, startValue, iterNo)
#define CREATE_LOOP_TAIL_INST(stNo, unrolledStNo, loopId, gotoPC, stepValue) MEMORY_PLATE::inst()->createLoopTailInstruction(stNo, unrolledStNo, loopId, gotoPC, stepValue)
#define CREATE_WAIT_INST(stNo, unrolledStNo, waitCycle, isStatic, scheduledCycle) MEMORY_PLATE::inst()->createWaitInstruction(stNo, unrolledStNo, waitCycle, isStatic, scheduledCycle)

class MemoryManager
{
public:
	//! singleton implementation
	static MemoryManager *inst();

	void changeCurrentLibrary(int libraryId_);
	void collectGarbage();
	VIR::BinaryExpression *createBinaryExpression(VIR::VirEnumerations::BinaryOperatorType opType_,
																								VIR::Expression *leftOp_, VIR::Expression *rightOp_);
	VIR::FloatingPoint *createFloatingPoint(float value_);
	VIR::RangeExpression *createFullRangeExpression();
	VIR::Identifier *createIdentifier(string name_);
	VIR::Integer *createInteger(int value_);
	BIR::LoopHeaderInstruction *createLoopHeaderInstruction(int statementNo_, string unrolledStatementNo_, int loopId, bool isStatic_, int startValue_, int iterationNumber_);
	BIR::LoopTailInstruction *createLoopTailInstruction(int statementNo_, string unrolledStatementNo_, int loopId_, int gotoPC_, int stepValue_);
	void createNewLibrary();
	VIR::VIRBase *createObject(VIR::VirEnumerations::KindType kind_);
	BIR::BIRBase *createObjectB(BIR::BIREnumerations::BIRKindType kind_);
	VIR::RangeExpression *createRangeExpression(int begin_, int increment_, int end_);
	VIR::UnaryExpression *createUnaryExpression(VIR::VirEnumerations::UnaryOperatorType opType_, VIR::Expression *operand_);
	BIR::WaitInstruction *createWaitInstruction(int statementNo_, string unrolledStatementNo_, int waitCycle_, bool isStatic_, int scheduledCycle_);

	int currLibraryId() const;

	void deleteLibrary(int libraryId_);

private:
	//! singleton implementation
	MemoryManager() : _currLibraryId(-1), _globalId(0), _globalIdB(0) {}
	MemoryManager(MemoryManager const &);
	void operator=(MemoryManager const &);

private:
#define CREATE_OBJECT_INSIDE(castType) (castType *)createObject(kt##castType)
	typedef std::vector<VIR::VIRBase *> ObjectVector;

	int _currLibraryId;
	ObjectVector *_currObjectVector;
	std::vector<BIR::BIRBase *> _birObjectVector;
	int _globalId;
	int _globalIdB;
	map<int, ObjectVector *> _objectsLibrary;
	static MemorySpace::MemoryManager *_singletonInst;
};

} // namespace MemorySpace

#endif // __MemoryManager_H__
