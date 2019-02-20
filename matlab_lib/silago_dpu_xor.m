function p = silago_dpu_xor(p0,pt)
    p = p0;
    for i=1:size(pt,2)
        p = bi2de(xor(de2bi(p,27), de2bi(pt(i),27)));
    end
end