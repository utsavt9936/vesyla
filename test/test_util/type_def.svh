
`ifndef _TYPE_DEF_
`define _TYPE_DEF_

import name_mangling::*;

typedef struct
{
	logic [REG_FILE_DATA_WIDTH-1 : 0] dataIn0;
	logic [REG_FILE_DATA_WIDTH-1 : 0] dataIn1;
	logic [REG_FILE_DATA_WIDTH-1 : 0] dataOut0;
	logic [REG_FILE_DATA_WIDTH-1 : 0] dataOut1;

	logic [REG_FILE_ADDR_WIDTH-1 : 0] addrIn0;
	logic [REG_FILE_ADDR_WIDTH-1 : 0] addrIn1;
	logic [REG_FILE_ADDR_WIDTH-1 : 0] addrOut0;
	logic [REG_FILE_ADDR_WIDTH-1 : 0] addrOut1;

	logic instStartIn0;
	logic addrenIn0;
	logic addrenIn1;
	logic addrenOut0;
	logic addrenOut1;
} RegData;

typedef struct
{
	int pc;
	logic [INSTR_WIDTH-1 : 0] currInst;
} SequencerData;

typedef struct
{
	logic readEn;
	logic writeEn;
	int writeAddress;
	logic [SRAM_WIDTH-1:0] data;
} SramData;

typedef enum 
{
	iBrnch 		= 'b1011,
	iDelay 		= 'b0111,
	iDpu   		= 'b0100,
	iForTail   	= 'b1001,
	iForHead  	= 'b1000,
	iJump  		= 'b0110,
	iRaccu 		= 'b1010,
	iRefi1 		= 'b0001,
	iRefi2 		= 'b0010,
	iRefi3 		= 'b0011,
	iRoute		= 'b1100,
	iSRAM_R		= 'b1101,
	iSRAM_W		= 'b1110,
	iSwb   		= 'b0101
} InstructionCode;

`endif //_TYPE_DEF_
