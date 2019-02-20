%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% BLAS Level 1
% res = asum (n, x, incx)
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Template data:
%   - n: number of elements
%   - incx: increment step
%   - col: number of column
%   - 
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

n = {{ n }};
incx = {{ incx }};

{% for i in range(col) %}
x_sram_{{i}} = ones(1, {{n}}/{{col}}); %! SRAM [0,{{i}}]
x_reg_{{i}} = ones(1, 32); %! RFILE [0,{{i}}]
res_reg_{{i}} = [0]; %! RFILE [0,{{i}}]
{% endfor %}

res_sram = [0]; %! SRAM [0,0];

for a=1:{{n}}/2/{{col}}/32
	{% for i in range(col) %}
	x_reg_{{i}} = x_sram_{{i}}((a-1)*32+1 :(a-1)*32+32);
	{% endfor %}
	{% for i in range(col) %}
	x_reg_{{i}}(0) = sum(x_reg_{{i}}.*1); %! DPU [0,{{i}}]
	res_{{i}} = res_{{i}} + x_reg_{{i}}(0); %! DPU [1,{{i}}]
	{% endfor %}
end

{% for i in range(col) %}
res_{{i}} = res_{{i}} + res_{{i}}; %! DPU [1,{{i}}]
{% endfor %}

