
% General testcase

% Features:
%  - Testing parenthesis

dst = [1:13]; %! RFILE<> [0,0]
addreg = [1:5]; %! RFILE<> [0,0]

k=1; %!RACCU_VAR
for i = 1:3
    dst(k) = addreg(i) + addreg(i+1); %! DPU [0,0]
    k = k+4;
end
