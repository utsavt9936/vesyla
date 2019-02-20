
r = 0; % base row in DRRA
c = 0; % base column in DRRA
rm = 0; % base row in DiMArch
cm = 0; % base column in DiMArch

K = 6144; % code block size
WORD_NO = K / 16;
DATA_WORD_NO = 16;
CRC_WORD_NO = 2;
poly_size = 24;

crc_poly = [1,1,0,0,0,0,1,1,0,0,1,0,0,1,1,0,0,1,1,1,1,1,0,1,1]; %!

code_block = zeros(1, WORD_NO); %! MEM<> [rm, cm]
data_in = zeros(1, DATA_WORD_NO); %! RFILE<> [r,c]
crc_rem = zeros(1, CRC_WORD_NO); %! RFILE<> [r,c]

for i = 1 : WORD_NO / DATA_WORD_NO
	data_in = code_block(i);

	for j = 1 : DATA_WORD_NO
		crc_rem = LFSR(data_in(j), crc_poly); %! DPU[]
	end
end

