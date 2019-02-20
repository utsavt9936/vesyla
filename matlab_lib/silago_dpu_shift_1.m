function p = silago_dpu_shift_1(u,h)
    h_temp = de2bi(h,32);
    p = zeros(1,4);
    for i=1:4
        temp = de2bi(u(i),27);
        if h_temp(8*i) == 1
            %u(i)
            %bi2de(h_temp((i-1)*8+1:(i-1)*8+7))
            p(i) = bi2de( circshift(temp,bi2de(h_temp((i-1)*8+1:(i-1)*8+7))) );
        end
    end
end