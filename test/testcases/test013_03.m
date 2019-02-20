
% loop statement testcase (static)

% Features:
%  - Having more than one statement inside a loop

inp = [1:16]; %! RFILE<> [0,0]
out = zeros(1, 16); %! RFILE<> [1,0]
acc = zeros(1, 1); %! RFILE<> [0,1]

for i = 1 : 3
	acc(1) = acc(1) + inp(i); %! DPU[0,1]
	out(i) = acc(1);
end
