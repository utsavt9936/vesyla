sub_image_1 = [1:16*128]; %! MEM <> [0,0]
sub_image_2 = [1:16*128]; %! MEM <> [0,1]
sub_image_3 = [1:16*128]; %! MEM <> [0,2]
sub_image_4 = [1:16*128]; %! MEM <> [0,3]

sub_block_top = zeros(1, 32); %! RFILE <> [0, 0]
sub_block_bot = zeros(1, 32); %! RFILE <> [0, 1]

result_top = zeros(1, 32); %! RFILE <> [0, 2]
result_bot = zeros(1, 32); %! RFILE <> [0, 3]

constants = [1 2 3 4 5 6 7 8 1024 1000]; %! RFILE <> [1, 0]
zero = [0]; %! RFILE <> [1, 0]

row_mid=5;
col_mid=5;

% center_block
  if col_mid == constants(1) %! DPU [1, 0]
    sub_block_top = sub_image_1(((col_mid-1)*8*64 + (row_mid-1)*64 + 1: (col_mid-1)*8*64 + (row_mid-1)*64 + 32));
    sub_block_bot = sub_image_1(((col_mid-1)*8*64 + (row_mid-1)*64 + 33: (col_mid-1)*8*64 + (row_mid-1)*64 + 64));
  elseif col_mid == constants(2)
    sub_block_top = sub_image_1(((col_mid-1)*8*64 + (row_mid-1)*64 + 1: (col_mid-1)*8*64 + (row_mid-1)*64 + 32));
    sub_block_bot = sub_image_1(((col_mid-1)*8*64 + (row_mid-1)*64 + 33: (col_mid-1)*8*64 + (row_mid-1)*64 + 64));
  elseif col_mid == constants(3)
    sub_block_top = sub_image_2(((col_mid-3)*8*64 + (row_mid-1)*64 + 1: (col_mid-3)*8*64 + (row_mid-1)*64 + 32));
    sub_block_bot = sub_image_2(((col_mid-3)*8*64 + (row_mid-1)*64 + 33: (col_mid-3)*8*64 + (row_mid-1)*64 + 64));
  elseif col_mid == constants(4)
    sub_block_top = sub_image_2(((col_mid-3)*8*64 + (row_mid-1)*64 + 1: (col_mid-3)*8*64 + (row_mid-1)*64 + 32));
    sub_block_bot = sub_image_2(((col_mid-3)*8*64 + (row_mid-1)*64 + 33: (col_mid-3)*8*64 + (row_mid-1)*64 + 64));
  elseif col_mid == constants(5)
    sub_block_top = sub_image_3(((col_mid-5)*8*64 + (row_mid-1)*64 + 1: (col_mid-5)*8*64 + (row_mid-1)*64 + 32));
    sub_block_bot = sub_image_3(((col_mid-5)*8*64 + (row_mid-1)*64 + 33: (col_mid-5)*8*64 + (row_mid-1)*64 + 64));
  elseif col_mid == constants(6)
    sub_block_top = sub_image_3(((col_mid-5)*8*64 + (row_mid-1)*64 + 1: (col_mid-5)*8*64 + (row_mid-1)*64 + 32));
    sub_block_bot = sub_image_3(((col_mid-5)*8*64 + (row_mid-1)*64 + 33: (col_mid-5)*8*64 + (row_mid-1)*64 + 64));
  elseif col_mid == constants(7)
    sub_block_top = sub_image_4(((col_mid-7)*8*64 + (row_mid-1)*64 + 1: (col_mid-7)*8*64 + (row_mid-1)*64 + 32));
    sub_block_bot = sub_image_4(((col_mid-7)*8*64 + (row_mid-1)*64 + 33: (col_mid-7)*8*64 + (row_mid-1)*64 + 64));
  elseif col_mid == constants(8)
    sub_block_top = sub_image_4(((col_mid-7)*8*64 + (row_mid-1)*64 + 1: (col_mid-7)*8*64 + (row_mid-1)*64 + 32));
    sub_block_bot = sub_image_4(((col_mid-7)*8*64 + (row_mid-1)*64 + 33: (col_mid-7)*8*64 + (row_mid-1)*64 + 64));
  end

for row=1:8
  for col=1:8
    if col == constants(1) %! DPU [1, 0]
      ref_block_top = sub_image_1(((col-1)*8*64 + (row-1)*64 + 1: (col-1)*8*64 + (row-1)*64 + 32));
      ref_block_bot = sub_image_1(((col-1)*8*64 + (row-1)*64 + 33: (col-1)*8*64 + (row-1)*64 + 64));
    elseif col == constants(2)
      ref_block_top = sub_image_1(((col-1)*8*64 + (row-1)*64 + 1: (col-1)*8*64 + (row-1)*64 + 32));
      ref_block_bot = sub_image_1(((col-1)*8*64 + (row-1)*64 + 33: (col-1)*8*64 + (row-1)*64 + 64));
    elseif col == constants(3)
      ref_block_top = sub_image_2(((col-3)*8*64 + (row-1)*64 + 1: (col-3)*8*64 + (row-1)*64 + 32));
      ref_block_bot = sub_image_2(((col-3)*8*64 + (row-1)*64 + 33: (col-3)*8*64 + (row-1)*64 + 64));
    elseif col == constants(4)
      ref_block_top = sub_image_2(((col-3)*8*64 + (row-1)*64 + 1: (col-3)*8*64 + (row-1)*64 + 32));
      ref_block_bot = sub_image_2(((col-3)*8*64 + (row-1)*64 + 33: (col-3)*8*64 + (row-1)*64 + 64));
    elseif col == constants(5)
      ref_block_top = sub_image_3(((col-5)*8*64 + (row-1)*64 + 1: (col-5)*8*64 + (row-1)*64 + 32));
      ref_block_bot = sub_image_3(((col-5)*8*64 + (row-1)*64 + 33: (col-5)*8*64 + (row-1)*64 + 64));
    elseif col == constants(6)
      ref_block_top = sub_image_3(((col-5)*8*64 + (row-1)*64 + 1: (col-5)*8*64 + (row-1)*64 + 32));
      ref_block_bot = sub_image_3(((col-5)*8*64 + (row-1)*64 + 33: (col-5)*8*64 + (row-1)*64 + 64));
    elseif col == constants(7)
      ref_block_top = sub_image_4(((col-7)*8*64 + (row-1)*64 + 1: (col-7)*8*64 + (row-1)*64 + 32));
      ref_block_bot = sub_image_4(((col-7)*8*64 + (row-1)*64 + 33: (col-7)*8*64 + (row-1)*64 + 64));
    elseif col == constants(8)
      ref_block_top = sub_image_4(((col-7)*8*64 + (row-1)*64 + 1: (col-7)*8*64 + (row-1)*64 + 32));
      ref_block_bot = sub_image_4(((col-7)*8*64 + (row-1)*64 + 33: (col-7)*8*64 + (row-1)*64 + 64));
    end
    if row < constants(4) %! DPU [1, 1]
      result_top((row-1)*8+col) = sum(abs(sub_block_top - ref_block_top)); %! DPU [0, 0]
    elseif row > constants(4)
      result_bot((row-4-1)*8+col) = sum(abs(sub_block_top - ref_block_top)); %! DPU [0, 0]
    elseif col ~= constants(5)
      result_top((row-1)*8+col) = sum(abs(sub_block_top - ref_block_top)); %! DPU [0, 0]
    else
      result_top((row-1)*8+col) = constants(9); %! DPU [0, 0]
    end
  end
end

min_top = min(result_top); %! RFILE <> [1, 0]
min_bot = min(result_bot); %! RFILE <> [1, 0]

final_result_row = [0]; %! RFILE <> [1, 0]
final_result_col = [0]; %! RFILE <> [1, 0]

for row=1:4
  for col=1:8
    if result_top((row-1)*8+col) == min_top  %! DPU [1, 0]
      final_result_row = row - constants(5);  %! DPU [1, 1]
      final_result_col = col - constants(5);  %! DPU [1, 2]
    elseif result_bot((row-1)*8+col) == min_bot
      final_result_row = row - constants(1);  %! DPU [1, 1]
      final_result_col = col - constants(5);  %! DPU [1, 2]
    end
  end
end
