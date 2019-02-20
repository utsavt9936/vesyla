ROW = 2;
COL = 5;
REG_DEPTH = 32;

r_a_0 = zeros(1, REG_DEPTH); %! RFILE [0,0]
r_a_1 = zeros(1, REG_DEPTH); %! RFILE [0,1]
r_a_2 = zeros(1, REG_DEPTH); %! RFILE [0,2]
r_a_3 = zeros(1, REG_DEPTH); %! RFILE [0,3]
r_b_0 = zeros(1, REG_DEPTH); %! RFILE [1,0]
r_b_1 = zeros(1, REG_DEPTH); %! RFILE [1,1]
r_b_2 = zeros(1, REG_DEPTH); %! RFILE [1,2]
r_b_3 = zeros(1, REG_DEPTH); %! RFILE [1,3]
r_ret = zeros(1, 16); %! RFILE [0,4]

m_a = ones(1, REG_DEPTH*(COL-1)); %! MEM [0,0]
m_b = ones(1, REG_DEPTH*(COL-1)*8); %! MEM [0,1]
m_ret = zeros(1, 16); %! MEM [0,0]

r_a_0 = m_a(0*REG_DEPTH+1:1*REG_DEPTH);
r_a_1 = m_a(1*REG_DEPTH+1:2*REG_DEPTH);
r_a_2 = m_a(2*REG_DEPTH+1:3*REG_DEPTH);
r_a_3 = m_a(3*REG_DEPTH+1:4*REG_DEPTH);
i=1;
%for i=1:8
	offset = (i-1)*REG_DEPTH*(COL-1);
	r_b_0 = m_b(offset+1+0*REG_DEPTH:offset+1*REG_DEPTH);
	r_b_1 = m_b(offset+1+1*REG_DEPTH:offset+2*REG_DEPTH);
	r_b_2 = m_b(offset+1+2*REG_DEPTH:offset+3*REG_DEPTH);
	r_b_3 = m_b(offset+1+3*REG_DEPTH:offset+4*REG_DEPTH);

	r_b_0(1) = sum(r_a_0 .* r_b_0); %! DPU [0,0]
	r_b_1(1) = sum(r_a_1 .* r_b_1); %! DPU [0,1]
	r_b_2(1) = sum(r_a_2 .* r_b_2); %! DPU [0,2]
	r_b_3(1) = sum(r_a_3 .* r_b_3); %! DPU [0,3]

	r_b_1(1) = r_b_0(1) + r_b_1(1); %! DPU [0,1]
	r_b_2(1) = r_b_1(1) + r_b_2(1); %! DPU [0,2]
	r_ret(i) = r_b_2(1) + r_b_3(1); %! DPU [0,3]
%end

m_ret = r_ret;


