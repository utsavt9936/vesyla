
% Indirect addressing testcase

% Features:
%  - Simple indirect addressing

EL_NUM = 16;

array = [1 : EL_NUM]; %! RFILE<> [0,0]

addr = [2]; %! RFILE<address> [0,0]

B = zeros(1,1); %! RFILE<> [0,1]

B = array(addr);
