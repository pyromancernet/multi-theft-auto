namespace EmbeddedLuaCode
{
	const char* const useful_h = R"~LUA~(
--
-- Utility color functions
--

function getColorValues(color)
	local alpha = bitExtract(color, 24, 8)
	local red = bitExtract(color, 16, 8)
	local green = bitExtract(color, 8, 8)
	local blue = bitExtract(color, 0, 8)
	return red, green, blue, alpha
end

function colorMulAlpha(color, alpha)
   return alpha == 255 and color or alpha == 0 and 0 or bitReplace(color, bitExtract(color, 24, 8) * alpha / 255, 24, 8)
end
	)~LUA~";
}