namespace EmbeddedLuaCode
{
	const char* const classic_h = R"~LUA~(
--[[
	SHARED CLASS SYSTEM
	Provides a simple class system for Lua.
	Supports inheritance and polymorphism.
	https://github.com/rxi/classic/blob/master/classic.lua
--]]

local object = {}
object.__index = object

function object:__tostring()
	return "object"
end

function object:__call(...)
	local instance = setmetatable({}, self)

	if instance.new then
		instance:new(...)
	end

	return instance
end

function object:isa(class)
	local metatable = getmetatable(self)

	while metatable do
		if metatable == class then
			return true
		end

		metatable = getmetatable(metatable)
	end

	return false
end

function object:extend()
	local class = {}

	for key, value in pairs(self) do
		if key:find("__") == 1 then
			class[key] = value
		end
	end

	class.__index = class
	class.__super = self

	setmetatable(class, self)
	return class
end

function object:implement(...)
	for _, class in pairs({...}) do
		for key, value in pairs(class) do
			if self[key] == nil and type(value) == "function" and key:find("__") ~= 1 then
				self[key] = value
			end
		end
	end
end

classic = setmetatable({}, object)
	)~LUA~";
}