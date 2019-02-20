Wr_reg = [4096, 0, 2859, -2859]; %! RFILE [0,1]
Wi_reg = [0, -4096, -2859, -2859]; %! RFILE [0,1]
Dr0_reg = [1448, 1448, 2648, 4345, 1448, -4345, -5544, -1448]; %! RFILE [0,0]
Di0_reg = [0, 0, 0, 0, 0, 0, 0, 0]; %! RFILE [1,0]
Dr1_reg = [0, 0, 0, 0, 0, 0, 0, 0]; %! RFILE [0,0]
Di1_reg = [0, 0, 0, 0, 0, 0, 0, 0]; %! RFILE [1,0]

Dr0_reg = __sl_bitreverse(Dr0_reg); %! DPU [0,0]
Di0_reg = __sl_bitreverse(Di0_reg); %! DPU [0,0]
__sl_load(Wr_reg, Wi_reg); %! DPU [0,0]

STAGE_NO=3;
N=8;

for stage = 1 : STAGE_NO
    r0        = stage+0;					%! RACCU_VAR
    half_size = bitsra(1, r0);		%! RACCU_VAR
    block_no  = bitsra(N, stage);	%! RACCU_VAR
    bn0       = block_no - 1;			%! RACCU_VAR
    for i = 0 : bn0
        twi = 1;									%! RACCU_VAR
        ri = bitsll(i, stage);		%! RACCU_VAR
        for j = 1 : half_size
            k = ri + j;						%! RACCU_VAR
            kh = k + half_size;		%! RACCU_VAR
            [ Dr0_reg(k), Di0_reg(k), Dr0_reg(kh), Di0_reg(kh) ] = __sl_butterfly(Dr0_reg(k), Di0_reg(k), Dr0_reg(kh), Di0_reg(kh), twi); %! DPU [0,0]
            twi = twi + block_no;	%! RACCU_VAR
        end
    end
end

