%t1 = (1900:10:1990)';
%t2 = (190:1:990)';

m4 = [ 75.995  91.972; 105.711 12 ; 123.203 11.1; 131.669, 423.2];

% m = zeros(t,1);

a = 0;

for i = 2 : M + 1 %! parallel
	m2 = [ i 2*i ];
	m3 = [ i i+1 ];

	a = a + m2(1) - m3(2);

	if (i == 3)
		m3 = m1(2:3);
	end
end

%(mm1501.m plot)
%plot(datenum(t,1,1),p)
%datetick('x','yyyy') % use 4-digit year on the x-axis
%title('Figure 15.1: Population by Year')
