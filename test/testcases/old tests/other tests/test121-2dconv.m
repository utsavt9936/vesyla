
% 2D Convolution

ROWS = 8; % row number
COLS = 8; % column number
K_ROWS = 3; % kernel row number
K_COLS = 3; % kernel column number

M = [1 2]; %! parallelism
N = ROWS*COLS; % data size
K = K_ROWS*K_COLS; % kernel size
B = (ROWS-2)*(COLS-2); % output size

inp = [1:N]; %! RFILE<> [r,c:c+M-1]
kernel = [1:K]; %! RFILE<dup> [r+1,c:c+M-1]
out = zeros(1, B); %! RFILE<> [r+1,c:c+M-1]_output

% Style 1
for row = 1 : ROWS-1
	for col = 1 : COLS-1
		for k_row = 1 : K_ROWS
			acc = sum(inp((row+k_row-2)*COLS+col : (row+k_row-2)*COLS+col+K_COLS-1) .* kernel((k_row-1)*K_COLS+1 : k_row*K_COLS);
		end

		out((row-1)*COLS + col) = acc;
	end
end

% Style 2
for row = 1 : ROWS-1
	for col = 1 : COLS-1
		for k_row = 1 : K_ROWS
			for k_col = 1 : K_COLS
				acc = sum(inp((row+k_row-2)*COLS+col+k_col-1) .* kernel((k_row-1)*K_COLS+k_col);
			end
		end

		out((row-1)*COLS + col) = acc;
	end
end

% for matlab printing
for row = 1 : 6
	for col = 1 : 6
		for k_row = 1 : 3
			for k_col = 1 : 3
				inp(k_row, k_col, col, row) = (row+k_row-2)*8 + col + k_col - 1;
				ker(k_row, k_col, col, row) = (k_row-1)*3 + k_col;
			end
		end
	end
end
