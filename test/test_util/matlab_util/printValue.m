
function str = printValue(value, isFixedPoint)

	if isFixedPoint == 1
		str = sprintf('%.4f ', value);
	else
		str = sprintf('%2d ', value);
	end

end
