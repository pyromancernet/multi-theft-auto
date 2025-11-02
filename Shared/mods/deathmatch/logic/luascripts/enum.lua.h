namespace EmbeddedLuaCode
{
	const char* const enum_h = R"~LUA~(
enum = function(...)
	local args = {...}

	if type(args[1]) == "string" then
		return function(list)
			_G[args[1]] = {}

			for i, v in ipairs(list) do
				_G[args[1]][v] = i
			end
		end
	else
		for i, v in ipairs(...) do
			_G[v] = i
		end
	end
end
	)~LUA~";
}