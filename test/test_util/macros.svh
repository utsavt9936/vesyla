
`ifndef _MACROS_
`define _MACROS_

// Some macro definitions for simpler access
`define fabricCell 			DUT.MTRF_COLS[col].MTRF_ROWS[row].SILEGO_cell.MTRF_cell
`define fabricRegTop 		`fabricCell.reg_top
`define aguAddressEn(port)	`fabricRegTop.AGU_``port``_instantiate.addr_en
`define aguAddress(port)	`fabricRegTop.AGU_``port``_instantiate.addr_out
`define regFileData(port)	`fabricRegTop.RegisterFile.``port
`define dimarchDataIn 		`fabricRegTop.dimarch_data_in
`define currRegVariable		regFileVariables[row][col][address]
`define currRegData 		regData[row][col]
`define currSequencerData	sequencerData[row][col]
`define currInstruction		`currSequencerData.currInst
`define currFixedPointStatus regFileFixedPointStatus[row][col][address]

`define stile				DUT.DiMArch_COLS[col].DiMArch_ROWS[row].u_STILE
`define sramReadEn			`stile.SRAM_rw_r
`define sramWriteEn			`stile.SRAM_rw_w
`define sramWriteAddress	`stile.SRAM_rw_addrs_out_w
`define sramMemData			`stile.memory_out
`define currSramData		sramData[0][col]

`endif //_MACROS_