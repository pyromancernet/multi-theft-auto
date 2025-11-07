/*
** $Id: lualib.h,v 1.36.1.1 2007/12/27 13:02:25 roberto Exp $
** Lua standard libraries
** See Copyright Notice in lua.h
** Modified by Pyromancer for Multi Theft Auto
*/

#ifndef lualib_h
	#define lualib_h

	#include "lua.h"

	// Key to file handle type
	#define LUA_FILEHANDLE		"FILE*"

	// Coroutine library
	#define LUA_COLIBNAME	"coroutine"
	LUALIB_API int (luaopen_base) (lua_State *L);

	// Table library
	#define LUA_TABLIBNAME	"table"
	LUALIB_API int (luaopen_table) (lua_State *L);

	// I/O library
	#define LUA_IOLIBNAME	"io"
	LUALIB_API int (luaopen_io) (lua_State *L);

	// OS library
	#define LUA_OSLIBNAME	"os"
	LUALIB_API int (luaopen_os) (lua_State *L);

	// String library
	#define LUA_STRLIBNAME	"string"
	LUALIB_API int (luaopen_string) (lua_State *L);

	// Math library
	#define LUA_MATHLIBNAME	"math"
	LUALIB_API int (luaopen_math) (lua_State *L);

	// Debug library
	#define LUA_DBLIBNAME	"debug"
	LUALIB_API int (luaopen_debug) (lua_State *L);

	// Package library
	#define LUA_LOADLIBNAME	"package"
	LUALIB_API int (luaopen_package) (lua_State *L);

	// open all previous libraries
	LUALIB_API void (luaL_openlibs) (lua_State *L); 

	// Adds UTF-8 support functions
	LUALIB_API int luaopen_utf8(lua_State *L);

	#ifndef lua_assert
		#define lua_assert(x)	((void)0)
	#endif
#endif