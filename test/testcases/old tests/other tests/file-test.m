
%{
 ! constants:
    M = 4;
    N = 200;
    row = 0;
    col_s = 0;
    col_e = col_s + M - 1;
%}

A = [1:200]; %! A -> RFILE [row, col_s:col_e] dist_even

%N = 200;
N = size(A, 2);
M = 4;

lSize = ceil(N / M);

% How can we use some parts of RFILE [row, col_s] instead of this?
B = zeros(M); %! B -> RFILE [row+1, col_s]

for t = 1 : M %! parallel_loop
	
    % address functions
	fIndex = 1 + (t - 1) * lSize;
    
    lIndex = fIndex + lSize - 1;
    if lIndex > N
        lIndex = N;        
    end
    
	B(t) = A(fIndex); %! what pragma?

	for i = fIndex + 1 : lIndex
        % Note: the column part of the pragma doesn't need a range,
        %       as the range can be inferred from the parallel_loop bounds.
		if A(i) < B(t) %! DPU [row, col_s]
			B(t) = A(i);
        end
        
        fprintf('i = %g\n', i);
    end
end

min = B(1); %! what pragma?

for t = 2 : M
    % Here we also can use DPU[row, col_s] because it has finished its execution.
	if B(t) < min  %! DPU [row+1, col_s]
		min = B(t);
	end
end


% using %! as a pragma notation


%{
 Register files distribution: (only possible when we are working with more than one DRRA cells)
  - dist_even: distribute evenly
  - full_cap : use the full capacity of a register file and then go for the next one.
  - custom   : use [ : ] [ : ] . . . for specific index separation
%}

%{
    "parallel_loop" determines the loop that should be distributed to several DRRA cells.
    TODO: see OpenMP for proper syntax.
%}
