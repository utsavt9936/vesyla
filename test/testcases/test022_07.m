
% Parallelization testcase

% Features:
%  - Defining a resource sharing region for MAC calculation

tf = fi([0.99999999 0.99999999 0.99999999 0.99999999 0.99999999 0.99999999 0.99999999 0.99999999 0.98078528 0.83146961 0.55557023 0.19509032 0.19509032 0.55557023 0.83146961 0.98078528 0.92387953 0.38268343 0.38268343 0.92387953 0.92387953 0.38268343 0.38268343 0.92387953 0.83146961 0.19509032 0.98078528 0.55557023 0.55557023 0.98078528 0.19509032 0.83146961 0.70710678 0.70710678 0.70710678 0.70710678 0.70710678 0.70710678 0.70710678 0.70710678 0.55557023 0.98078528 0.19509032 0.83146961 0.83146961 0.19509032 0.98078528 0.55557023 0.38268343 0.92387953 0.92387953 0.38268343 0.38268343 0.92387953 0.92387953 0.38268343 0.19509032 0.55557023 0.83146961 0.98078528 0.98078528 0.83146961 0.55557023 0.19509032], 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE<input> [0:1,0]
x  = fi([0.003601 0.003601 0.003662 0.003723 0.003815 0.003845 0.003540 0.003418 0.003479 0.003845 0.004120 0.004242 0.004303 0.004456 0.005096 0.003662 0.002014 0.001404 0.001831 0.002319 0.002106 0.001648 0.001831 0.001770 0.001617 0.001495 0.001404 0.001404 0.001465 0.001495 0.001831 0.001770 0.001740 0.001740 0.001801 0.001831 0.001801 0.001740 0.001556 0.001648 0.001801 0.001923 0.001923 0.001831 0.001678 0.001526 0.001343 0.001251 0.001343 0.001526 0.001526 0.001343 0.001251 0.001343 0.001740 0.001740 0.001740 0.001740 0.001740 0.001740 0.001740 0.001740 0.001465 0.001465 ], 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE<input> [0:1,2]
X  = fi(zeros(1,64), 1, 16, 15, 'RoundingMethod', 'Floor'); %! RFILE<output> [0:1,1]

% %! RESOURCE_SHARING_BEGIN
X(1) = sum(fi(x(1:8) .* tf(1:8), 1, 16, 15, 'RoundingMethod', 'Floor')); %! DPU<sat> [0,1]
X(33) = sum(fi(x(33:40) .* tf(1:8), 1, 16, 15, 'RoundingMethod', 'Floor')); %! DPU<sat> [1,1]
% %! RESOURCE_SHARING_END