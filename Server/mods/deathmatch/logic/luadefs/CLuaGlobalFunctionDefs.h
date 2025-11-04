/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/luadefs/CLuaGlobalFunctionDefs.h
 *  PURPOSE:     Lua global function definitions class for cross-resource functions
 *
 *  Multi Theft Auto is available from https://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#include "CLuaDefs.h"

class CLuaGlobalFunctionDefs : public CLuaDefs
{
public:
    static void LoadFunctions();

    // Global function system
    LUA_DECLARE(RegisterGlobalFunction);
    LUA_DECLARE(CallGlobalFunction);
    LUA_DECLARE(HasGlobalFunction);
    LUA_DECLARE(RemoveGlobalFunction);
    LUA_DECLARE(GetGlobalFunctions);
};
