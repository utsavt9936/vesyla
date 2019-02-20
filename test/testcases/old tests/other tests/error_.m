sub_image = [1:16*128]; %! MEM <> [0,0]

sub_block_top = [1:32]; %! RFILE <> [0, 1]
sub_block_bot = [1:32]; %! RFILE <> [1, 1]

ref_block_top = [1:32]; %! RFILE <> [0, 0]
ref_block_bot = [1:32]; %! RFILE <> [1, 0]

result_top = [1:32]; %! RFILE <> [0, 2]
result_bot = [1:32]; %! RFILE <> [1, 2]

temp_top = [1:32]; %! RFILE <> [0, 4]
temp_bot = [1:32]; %! RFILE <> [1, 4]

constants = [1 2 3 4 5 6 7 8]; %! RFILE <> [0, 3]
zero = [0]; %! RFILE <> [0, 3]

min_top = [0]; %! RFILE <> [1, 3]
min_bot = [0]; %! RFILE <> [1, 3]

for row=1:4
  for col=1:8
    ref_block_top(1:32) = sub_image((row-1)*32 + (col-1)*128 + 1:row*32 + (col-1)*128 + 32);
    ref_block_bot(1:32) = sub_image((row-1)*32 + (col-1)*128 + 33:row*32 + (col-1)*128 + 64);
    temp_top = sub_block_top - ref_block_top; %! DPU [0, 2]
    result_bot((row-1)*8+col) = sum(temp_top); %! DPU [0, 2]
  end
end
