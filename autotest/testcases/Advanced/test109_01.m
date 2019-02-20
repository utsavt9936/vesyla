
%  Huffman testcase

% Features:
%  - Huffman

index = [1:256]; %! MEM<> [0, 0]
table = [1:256]; %! MEM<> [0, 1]

x = [1:32]; %! RFILE<input> [1, 0]
y = zeros(1, 32); %! RFILE<output> [1, 1]

rindex = [1:32]; %! RFILE<> [0, 0]
rtable = [1:32]; %! RFILE<> [0, 1]

rindex = index(1:32);
rtable = table(1:32);

for src=1:32
  for tab=1:32
    if rindex(tab) == x(src) %! DPU [1,1]
      y(src) = rtable(tab);
    end
  end
end



%x = zeros(1, 64); %! RFILE<input> [0, 0:1]
%y = zeros(1, 64); %! RFILE<output> [1, 0:1]

% rindex = [1:64]; %! RFILE<> [0, 2:3]
% rtable = [1:64]; %! RFILE<> [1, 2:3]

% rindex = index(1:64);
% rtable = table(1:64);

% for src=1:64
%   for tab=1:64
%     if rindex(tab) == x(src)
%       y(src) = rtable(tab);
%     end
%   end
% end

% rindex = index(65:128);
% rtable = table(65:128);
% for src=1:64
%   for tab=1:64
%     if rindex(tab) == x(src)
%       y(src) = rtable(tab);
%     end
%   end
% end

% rindex = index(129:192);
% rtable = table(129:192);
% for src=1:64
%   for tab=1:64
%     if rindex(tab) == x(src)
%       y(src) = rtable(tab);
%     end
%   end
% end

% rindex = index(193:256);
% rtable = table(193:256);
% for src=1:64
%   for tab=1:64
%     if rindex(tab) == x(src)
%       y(src) = rtable(tab);
%     end
%   end
% end
