function hp = silago_dpu_shift_hp1(p,h)
    hp = zeros(1,4);
    h_temp = de2bi(h,32);
    for i = 1:4
        if h_temp(i*8) == 1
        hp(i) = bi2de(circshift(de2bi(p,27), bi2de(h_temp((i-1)*8+1:(i-1)*8+7))) );
        end
    end
end