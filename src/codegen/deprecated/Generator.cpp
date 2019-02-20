#include "Generator.hpp"

using namespace vesyla::schedule;

namespace vesyla
{
namespace codegen
{

int get_real_dimarch_row(int row_)
{
	return (row_ + 1);
}

BIR::RouteInstruction *Generator::create_route_instr(int statementNo_, const VIR::Coordinate &memoryCoord_, const VIR::Coordinate &regFileCoord_, bool isMemToRegTrans_, const string variableName_)
{
	RouteInstruction *routeInst = CREATE_OBJECT_B(RouteInstruction);

	routeInst->variableName = variableName_;
	routeInst->statementNo = statementNo_;
	routeInst->unrolledStatementNo = "0";
	routeInst->drraSelect = regFileCoord_.row;
	routeInst->isFromSource = isMemToRegTrans_;
	const int real_dimarch_row = get_real_dimarch_row(memoryCoord_.row);
	if (isMemToRegTrans_)
	{
		routeInst->sourceCoordinate = Coordinate(real_dimarch_row, memoryCoord_.column);
		routeInst->destCoordinate = Coordinate(0, regFileCoord_.column);
	}
	else
	{
		routeInst->sourceCoordinate = Coordinate(0, regFileCoord_.column);
		routeInst->destCoordinate = Coordinate(real_dimarch_row, memoryCoord_.column);
	}
	return routeInst;
}

RACCUInstruction *Generator::create_raccu_instr(int statementNo_,
																								BIR::BIREnumerations::RACCUMode raccuMode_, int operand1_,
																								bool isOp1Static_, int operand2_, bool isOp2Static_,
																								int resultAddress_)
{
	RACCUInstruction *raccuInst = CREATE_OBJECT_B(RACCUInstruction);
	raccuInst->statementNo = statementNo_;
	raccuInst->unrolledStatementNo = "";
	raccuInst->raccuMode = raccuMode_;
	raccuInst->dependentTo = NULL;
	raccuInst->operand1(operand1_, isOp1Static_);
	raccuInst->operand2(operand2_, isOp2Static_);
	raccuInst->resultAddress = resultAddress_;
	return raccuInst;
}

int Generator::reserve_raccu_var(int statementNo_, VIR::AddressFunction af_, VIR::Coordinate coord_)
{
	int raccu_var_index = _raccu_var_manager.push(coord_);
	RACCUInstruction *raccu_head = create_raccu_instr(statementNo_, rmAdd, af_.b(), true, 0, true, raccu_var_index);
	int earliest_loop_statement_no = INT_MAX;
	ForStatement *earliest_loop_ptr = NULL;
	for (int i = 0; i < af_.level(); i++)
	{
		if (af_.l(i)->statementNo() < earliest_loop_statement_no)
		{
			earliest_loop_statement_no = af_.l(i)->statementNo();
			earliest_loop_ptr = af_.l(i);
		}
		RACCUInstruction *raccu_tail = create_raccu_instr(statementNo_, rmAdd, raccu_var_index, false, af_.a(i), true, raccu_var_index);
		af_.l(i)->add_tail_raccu_instr(raccu_tail, coord_);
	}
	earliest_loop_ptr->add_head_raccu_instr(raccu_head, coord_);
	return raccu_var_index;
}

SRAMInstruction *Generator::create_sram_instr(VIR::SliceName *sliceName_, int statementNo_, const VIR::Coordinate &memoryCoord_,
																							const VIR::Coordinate &regFileCoord_,
																							bool isMemToRegTrans_, int memoryStartAddr_,
																							const string variableName_)
{
	SramAddressTransformer t;
	SRAMInstruction *sramInst = CREATE_OBJECT_B(SRAMInstruction);
	sramInst->variableName = variableName_;
	sramInst->statementNo = statementNo_;
	sramInst->unrolledStatementNo = "";
	sramInst->isRead = isMemToRegTrans_;
	sramInst->correspondingRefiInst = NULL;
	sramInst->correspondingRouteInst = NULL;
	sramInst->initialDelay(0, true);
	sramInst->loop1Delay(t.get_sram_agu_middle_delay(), true);
	sramInst->loop2Delay(t.get_sram_agu_repetition_delay(), true);

	VIR::Address addr = t.transform(sliceName_->addr);
	sliceName_->addr = addr;

	// adjust the offset of b so that it start from the correct position in the
	// storage. +memoryStartAddr is to shift it to the starting address of the
	// variable. -1 is to cancel the difference between matlab index and HW index
	// system, matlab index start from 1 instead of 0.
	addr.b.b(addr.b.b() + memoryStartAddr_ - 1);
	if (addr.b.is_constant())
	{
		sramInst->initialAddress(addr.b.b(), true);
	}
	else
	{
		// Here, a raccu variable will be created to calclate the dynamic address, the
		// raccu instructions will be created and associated with corresponding loops,
		// but the raccu instructions will not be added to instruction list immediately,
		// For loop will be responsible to add all raccu instructions accociated with
		// it.
		int raccu_var_id = reserve_raccu_var(statementNo_, addr.b, regFileCoord_);
		sramInst->initialAddress(raccu_var_id, false);
	}

	if (addr.a0.is_constant())
	{
		sramInst->loop1Increment = addr.a0.b();
	}
	else
	{
		LOG(FATAL) << "Increment can't be dynamic!";
	}

	if (addr.n0.is_constant())
	{
		sramInst->loop1Iterations(addr.n0.b(), true);
	}
	else
	{
		LOG(FATAL) << "Iteration can't be dynamic!";
	}

	if (addr.a1.is_constant())
	{
		sramInst->loop2Increment = addr.a0.b();
	}
	else
	{
		LOG(FATAL) << "Increment can't be dynamic!";
	}

	if (addr.n0.is_constant())
	{
		sramInst->loop2Iterations(addr.n1.b(), true);
	}
	else
	{
		LOG(FATAL) << "Iteration can't be dynamic!";
	}
	return sramInst;
}

void Generator::create_instr_for_memory_transfer(VIR::AssignmentStatement *statement_, schedule::Descriptor &d_, string path_, int child_group_)
{
	StoragePragma *lhs_pragma = static_cast<StoragePragma *>((statement_->lhsIdentifiers())[0]->object()->pragma());
	StoragePragma *rhs_pragma = static_cast<StoragePragma *>((statement_->rhsIdentifiers())[0]->object()->pragma());
	SliceName *lhs_slice_name = static_cast<SliceName *>(statement_->lhs()[0]);
	SliceName *rhs_slice_name = static_cast<SliceName *>(statement_->rhs());

	StoragePragma *mem_pragma;
	StoragePragma *reg_pragma;
	SliceName *reg_slice_name;
	SliceName *mem_slice_name;
	bool is_mem_to_reg;

	CHECK(lhs_pragma) << ("Improper memory transfer statement!");
	CHECK(rhs_pragma) << ("Improper memory transfer statement!");
	CHECK(lhs_slice_name) << ("Improper memory transfer statement!");
	CHECK(rhs_slice_name) << ("Improper memory transfer statement!");

	if (lhs_pragma->storageType() == stRegFile && rhs_pragma->storageType() == stMemory)
	{
		is_mem_to_reg = true;
		mem_pragma = rhs_pragma;
		reg_pragma = lhs_pragma;
		mem_slice_name = rhs_slice_name;
		reg_slice_name = lhs_slice_name;
	}
	else
	{
		is_mem_to_reg = false;
		mem_pragma = lhs_pragma;
		reg_pragma = rhs_pragma;
		mem_slice_name = lhs_slice_name;
		reg_slice_name = rhs_slice_name;
	}

	// Assuming mem_pragma and reg_pragma only involve one cell each.
	// This assumption is reasonable because if multiple memory transfer need to be
	// done, it's equavalent to generate multiple memory transfter statements. The
	// break down process should be handled in elaboration phase.
	// TODO: Add the support to translate multi-cell assignment to multiple assignment
	// statements during elaboration.

	CHECK_EQ(mem_pragma->coordinates.size(), 1) << "Multi-cell assignment detected!";
	CHECK_EQ(reg_pragma->coordinates.size(), 1) << "Multi-cell assignment detected!";

	const Coordinate &mem_coord = mem_pragma->coordinates[0];
	const Coordinate &reg_coord = reg_pragma->coordinates[0];

	RouteInstruction *route_instr = create_route_instr(statement_->statementNo(), mem_coord, reg_coord, is_mem_to_reg, mem_slice_name->prefix()->name());
	RefiInstruction *refi_instr = NULL; // create_refi_instr();
	SRAMInstruction *sram_instr = create_sram_instr(mem_slice_name, statement_->statementNo(), mem_coord, reg_coord, is_mem_to_reg, mem_pragma->startAddresses[0], mem_slice_name->prefix()->name());

	string signature = to_string(reg_coord.row) + "_" + to_string(reg_coord.column);
	d_.add_instruction(signature, route_instr);
	d_.add_instruction(signature, refi_instr);
	d_.add_instruction(signature, sram_instr);

	//descriptor interface
	SramAddressTransformer t(16, 16);
	map<string, vector<vector<int>>> rot0, rot2;
	rot0[to_string(reg_coord.row) + "_" + to_string(reg_coord.column) + "_SEQ"].push_back({0, 0});
	int start_r = 0;
	int start_c = reg_coord.column;
	int end_r = mem_coord.row;
	int end_c = mem_coord.column;
	for (int i = start_r; i <= end_r; i++)
	{
		rot0[to_string(i) + "_" + to_string(start_c) + "_DIMARCH"].push_back({0, INT_MAX});
		rot2[to_string(i) + "_" + to_string(start_c) + "_DIMARCH"].push_back({INT_MIN, 0});
	}
	if (start_c < end_c)
	{
		for (int i = start_c + 1; i <= end_c; i++)
		{
			rot0[to_string(end_r) + "_" + to_string(i) + "_DIMARCH"].push_back({0, INT_MAX});
			rot2[to_string(end_r) + "_" + to_string(i) + "_DIMARCH"].push_back({INT_MIN, 0});
		}
	}
	else if (start_c > end_c)
	{
		for (int i = start_c - 1; i >= end_c; i--)
		{
			rot0[to_string(end_r) + "_" + to_string(i) + "_DIMARCH"].push_back({0, INT_MAX});
			rot2[to_string(end_r) + "_" + to_string(i) + "_DIMARCH"].push_back({INT_MIN, 0});
		}
	}

	schedule::Operation o_route0(d_.gen_signature(path_), 0, rot0);
	schedule::Operation o_route1(d_.gen_signature(path_), 0, {});
	schedule::Operation o_route2(d_.gen_signature(path_), 0, rot2);
	d_.add_operation(o_route0);
	d_.add_operation(o_route1);
	d_.add_operation(o_route2);
	d_.get_mutable_operation(path_).add_children({o_route0.name(), o_route1.name(), o_route2.name()}, child_group_);
	route_instr->labels.push_back(o_route0.name());
	route_instr->labels.push_back(o_route1.name());
	route_instr->labels.push_back(o_route2.name());
	d_.add_constraint(Constraint(o_route0.name(), o_route1.name(), t.get_sram_refi_distance(reg_coord, mem_coord), t.get_sram_refi_distance(reg_coord, mem_coord)));
	d_.add_constraint(Constraint(o_route1.name(), o_route2.name(), 1, INT_MAX));

	string res_name = "";
	int num_of_addr = refi_instr->numberOfAddress.value + 1;
	int exe_cycle = (num_of_addr + (num_of_addr - 1) * refi_instr->middleDelay.value) + ((num_of_addr + (num_of_addr - 1) * refi_instr->middleDelay.value) - 1) * refi_instr->repetitionDelay.value;
	if (is_mem_to_reg)
	{
		res_name = to_string(reg_coord.row) + "_" + to_string(reg_coord.column) + "_AGU0";
		refi_instr->portNo = 0;
	}
	else
	{
		res_name = to_string(reg_coord.row) + "_" + to_string(reg_coord.column) + "_AGU2";
		refi_instr->portNo = 2;
	}
	schedule::Operation o_refi0(d_.gen_signature(path_), 0, {{to_string(reg_coord.row) + "_" + to_string(reg_coord.column) + "_SEQ", {{0, 0}}}, {res_name, {{0, INT_MAX}}}});
	schedule::Operation o_refi1(d_.gen_signature(path_), 0, {});
	schedule::Operation o_refi2(d_.gen_signature(path_), 0, {{res_name, {{INT_MAX, 0}}}});
	d_.add_operation(o_refi0);
	d_.add_operation(o_refi1);
	d_.add_operation(o_refi2);
	d_.get_mutable_operation(path_).add_children({o_refi0.name(), o_refi1.name(), o_refi2.name()}, child_group_);
	refi_instr->labels.push_back(o_refi0.name());
	refi_instr->labels.push_back(o_refi1.name());
	refi_instr->labels.push_back(o_refi2.name());
	d_.add_constraint(Constraint(o_refi0.name(), o_refi1.name(), 0, INT_MAX));
	d_.add_constraint(Constraint(o_refi0.name(), o_refi1.name(), exe_cycle / 16 - 1, exe_cycle / 16 - 1));
	d_.add_constraint(Constraint(o_route1.name(), o_refi1.name(), 1, INT_MAX));
	d_.add_constraint(Constraint(o_refi2.name(), o_route2.name(), 0, INT_MAX));

	schedule::Operation o_sram0(d_.gen_signature(path_), 0, {{to_string(reg_coord.row) + "_" + to_string(reg_coord.column) + "_SEQ", {{0, 0}}}});
	schedule::Operation o_sram1(d_.gen_signature(path_), 0, {});
	schedule::Operation o_sram2(d_.gen_signature(path_), 0, {});
	schedule::Operation o_sram3(d_.gen_signature(path_), 0, {});
	d_.add_operation(o_sram0);
	d_.add_operation(o_sram1);
	d_.add_operation(o_sram2);
	d_.add_operation(o_sram3);
	d_.get_mutable_operation(path_).add_children({o_sram0.name(), o_sram1.name(), o_sram2.name(), o_sram3.name()}, child_group_);
	sram_instr->labels.push_back(o_sram0.name());
	sram_instr->labels.push_back(o_sram1.name());
	sram_instr->labels.push_back(o_sram2.name());
	sram_instr->labels.push_back(o_sram3.name());
	d_.add_constraint(Constraint(o_sram0.name(), o_sram1.name(), t.get_sram_agu_init_delay_min(reg_coord, mem_coord), t.get_sram_agu_init_delay_min(reg_coord, mem_coord)));
	d_.add_constraint(Constraint(o_sram1.name(), o_sram2.name(), 0, INT_MAX));
	d_.add_constraint(Constraint(o_sram2.name(), o_sram3.name(), sram_instr->executionCycle - 1, sram_instr->executionCycle - 1));
	if (is_mem_to_reg)
	{
		d_.add_constraint(Constraint(o_sram2.name(), o_refi1.name(), t.get_sram_refi_distance(reg_coord, mem_coord), t.get_sram_refi_distance(reg_coord, mem_coord)));
	}
	else
	{
		d_.add_constraint(Constraint(o_refi1.name(), o_sram2.name(), t.get_sram_refi_distance(reg_coord, mem_coord), t.get_sram_refi_distance(reg_coord, mem_coord)));
	}
	d_.add_constraint(Constraint(o_route1.name(), o_sram2.name(), 1, INT_MAX));
	d_.add_constraint(Constraint(o_sram3.name(), o_route2.name(), 0, INT_MAX));
}

} // namespace codegen
} // namespace vesyla
