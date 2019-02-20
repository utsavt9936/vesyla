
`include "macros.svh"
import name_mangling::*;
import test_util::*;

// A module declaration to fill the package data arrays with the corresponding FABRIC signals
module fill_data;
	generate
		for (genvar row = 0; row < ROWS; row++)
			for (genvar col = 0; col < COLUMNS; col++)
			begin
				// Correspondence: AGU_Wr_0 -> data_in_0; AGU_Wr_1 -> data_in_1; AGU_Rd_0 -> data_out_reg_0_left; AGU_Rd_1 -> data_out_reg_1_left;
				assign `currRegData.dataIn0 		= `regFileData(data_in_0);
				assign `currRegData.dataIn1 		= `regFileData(data_in_1);
				assign `currRegData.dataOut0 		= `regFileData(data_out_reg_0_left);
				assign `currRegData.dataOut1 		= `regFileData(data_out_reg_1_left);
				assign `currRegData.addrIn0 		= `aguAddress(Wr_0);
				assign `currRegData.addrIn1 		= `aguAddress(Wr_1);
				assign `currRegData.addrOut0 		= `aguAddress(Rd_0);
				assign `currRegData.addrOut1 		= `aguAddress(Rd_1);
				assign `currRegData.addrenIn0 		= `aguAddressEn(Wr_0);
				assign `currRegData.addrenIn1 		= `aguAddressEn(Wr_1);
				assign `currRegData.addrenOut0		= `aguAddressEn(Rd_0);
				assign `currRegData.addrenOut1		= `aguAddressEn(Rd_1);
				assign `currRegData.instStartIn0	= `fabricRegTop.AGU_Wr_0_instantiate.instr_start;

				assign `currSequencerData.pc 		= `fabricCell.seq_gen.pc;
				assign `currSequencerData.currInst 	= `fabricCell.seq_gen.instr;
			end
	endgenerate

	generate
		for (genvar row = 0; row < ROWS-1; row++)
			for (genvar col = 0; col < COLUMNS; col++)
			begin
				assign `currSramData.readEn 		= `sramReadEn;
				assign `currSramData.writeEn		= `sramWriteEn;
				assign `currSramData.writeAddress 	= `sramWriteAddress;
				assign `currSramData.data 			= `sramMemData;
			end
	endgenerate

	initial
		for (int row = 0; row < ROWS; row++)
			for (int col = 0; col < COLUMNS; col++)
				oldpcs[row][col] = -1;
endmodule
