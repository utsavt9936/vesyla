% DNA sequencing algorithm through Self Organizing Algorithms (SOM)
% Algorithm translated from C++ to Matlab for Vesyla
% Translated by Prashant Sharma
% For the Silago Platform 

% Concept-parallelized for 2 Silago blocks

W1      = [1, 1, 1, 1]; %! RFILE<> [0,0]  	%(8 w1/// total 23) regfile space for storing weights of a specific neuron on silago block(0,0)
W2      = [1, 1, 1, 1]; %! RFILE<> [0,1]   	% regfile space for storing weights of a specific neuron on silago block(0,1)
In1     = [1 1]; %! RFILE<> [0,0]            	% input seq neuron on silago block(0,0)                
In2     = [1 1];  %! RFILE<> [0,1] 	   	% input seq neuron on silago block(0,1)
C       = [1 1 1 0 1 0]; %! RFILE<> [0,0]    	% ----[curr. prev_best.  seq_t temp2]          store weight sum sq         
D       = [1 1 1 0 1 0]; %! RFILE<> [0,1] 	% ----[curr. prev_best.  seq_t temp2]
Cd      = [0 1 0 0 1 0 0 1]; %! RFILE<> [0,0]   % ----[global_loc curr_loc temp dummy update temp3 local_best]
Dd      = [0 1 0 0 1 0 0 1]; %! RFILE<> [0,1]   % ----[global_loc curr_loc temp dummy update temp3 local_best]

for i = 1:2                                % pick new SOM
    for j = 1:2                                     % pick new neuron
           Cd(3)=sum(abs(Cd(2)-Cd(1))); %! DPU [0,0]   % compute difference between locations
           Dd(3)=sum(abs(Dd(2)-Dd(1))); %! DPU [0,1]   % repeat for other block

           if Cd(3)>8    %! DPU [0,0]                  % check if other path of the ring is shorter
                 Cd(3)=Cd(3)+16;   %! DPU [0,0]	       % store new path
           end

           if Dd(3)>8    %! DPU [0,1]                  % repeat for other block
                 Dd(3)=Dd(3)+16;   %! DPU [0,1]        
           end 

%            Cd(6)= Cd(6)-Cd(6);  %! DPU [0,0]          %* 4 dummy instruction
%            Dd(6)= Dd(6)-Dd(6);  %! DPU [0,1]          % dummy instruction for other block
                      
                     
%                     Cd(6)= Cd(6)+2;  %! DPU [0,0]               % *2 increment position 
%                     Dd(6)= Dd(6)+2;  %! DPU [0,1]               % repeat for other block
%                     
%                     Cd(4)= Cd(8)-Cd(6);   %! DPU [0,0]          % *3 difference between curren loactiona and best location to calculate update factor
%                     Dd(4)= Cd(8)-Cd(6);   %! DPU [0,1]          % repeat for other block

		for l=1:2        %CHAGEW HERE AND AKE IT 8 WEIGHHTS
						% load from SRAM to RFILE for input sequence.
						
						Cd(4) = 2; %! DPU [0,0]
						Dd(4) = 2; %! DPU [0,1]
						for k=1:2 % each weight
							
							% Bug: RACCU instruction only add a constant number.
%							ss = k+l;

                     Cd(4)= Cd(4)+0;  %! DPU [0,0]               % *2 increment position 
                     Dd(4)= Dd(4)+0;  %! DPU [0,1]               % repeat for other block
 
                     C(3) =bitsll(In1(1), Cd(4));   %! DPU [0,0]  % *1 seq unraping from input (It should use bitsll, modified version. to unpack the input to form DD00000000000000)
                     D(3) =bitsll(In2(1), Dd(4));   %! DPU [0,1]  % repeat for other block

                     if Cd(3)< Cd(5)   %! DPU [0,0]              % check for previous best neuron and then update          
                          C(4) = W1(k) - C(3);      %! DPU [0,0]       % **equ1**   (data-seq)             
                          C(4) = bitsra(C(4),Cd(3)); %! DPU [0,0]      % **equ2**  bitsra(a,2);%! DPU [0,0]   %alpha
                          W1(k) = W1(k) - C(4);     %! DPU [0,0]       % **equ3**  data - last
                     end
                     if Dd(3)< Dd(5)   %! DPU [0,1]              % repeat for other block                      
                          D(4) = W2(k) - D(3);      %! DPU [0,1]
                          D(4) = bitsra(D(4),Dd(3)); %! DPU [0,1]
                          W2(k) = W2(k) - D(4);	%! DPU [0,1]
                     end

                    W1(k)=W1(k)-C(3); %! DPU [0,0]    % **equ4** (W-seq)
                    W2(k)=W2(k)-D(3); %! DPU [0,1]    % repeat for other block
            end 

					C(6)=sum(W1.*W1); %! DPU [0,0]    % repeat for other block
          C(1) = C(1)+C(6); %! DPU [0,0]    % **equ5** square and summation for distance formula(no need to take square root as result doesnot change)
          D(6)=sum(W2.*W2);  %! DPU [0,1]    % repeat for other block
          D(1) = D(1)+D(6); %! DPU [0,1]    % repeat for other block
      end
          if C(1) < C(2) %! DPU [0,0]    % find best from curent silago block
             C(2)=C(1);                    % save value
             Cd(7)=Cd(2);                  % save location
          end

          if D(1) < D(2) %! DPU [0,1]    % repeat for other block
             D(2)=D(1);
             Dd(7)=Dd(2);
          end
    end
						% bug: condition should execute on both DRRA cells.
          if C(2) > D(2) %! DPU [0, 0:1]    % find best from both blocks(global best)  window size =2 is enough.
             Cd(1)=Dd(2);
             Dd(1)=Dd(2);
          else                           % repeat for opposite case
             Cd(1)=Cd(2);                     % save value
             Dd(1)=Cd(2);                     % cast to other block
          end
end
