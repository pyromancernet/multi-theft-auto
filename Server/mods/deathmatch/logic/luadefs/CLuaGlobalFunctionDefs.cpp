/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/luadefs/CLuaGlobalFunctionDefs.cpp
 *  PURPOSE:     Lua global function definitions class for cross-resource functions
 *
 *  Multi Theft Auto is available from https://www.multitheftauto.com/
 *
 *****************************************************************************/

#include "StdInc.h"
#include "CLuaGlobalFunctionDefs.h"
#include "CScriptArgReader.h"
#include "CStaticFunctionDefinitions.h"

void CLuaGlobalFunctionDefs::LoadFunctions()
{
    constexpr static const std::pair<const char*, lua_CFunction> functions[]
    {
        {"registerGlobalFunction", RegisterGlobalFunction},
        {"callGlobalFunction", CallGlobalFunction},
        {"hasGlobalFunction", HasGlobalFunction},
        {"removeGlobalFunction", RemoveGlobalFunction},
        {"getGlobalFunctions", GetGlobalFunctions},
    };

    // Add all functions
    for (const auto& [name, func] : functions)
        CLuaCFunctions::AddFunction(name, func);
}

int CLuaGlobalFunctionDefs::RegisterGlobalFunction(lua_State* luaVM)
{
    // registerGlobalFunction(string name, function func)
    SString strFunctionName;
    
    CScriptArgReader argStream(luaVM);
    argStream.ReadString(strFunctionName);

    if (!argStream.HasErrors())
    {
        // Check if the second argument is a function
        if (!lua_isfunction(luaVM, 2))
        {
            argStream.SetCustomError("Expected function as second argument");
        }
        else
        {
            // Push the function to the top of the stack
            lua_pushvalue(luaVM, 2);
            
            // Register it globally
            CLuaCFunctions::RegisterGlobalFunction(strFunctionName, luaVM);
            
            lua_pushboolean(luaVM, true);
            return 1;
        }
    }

    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaGlobalFunctionDefs::CallGlobalFunction(lua_State* luaVM)
{
    // callGlobalFunction(string name, [args...])
    SString strFunctionName;
    
    CScriptArgReader argStream(luaVM);
    argStream.ReadString(strFunctionName);

    if (!argStream.HasErrors())
    {
        // Get number of arguments (excluding the function name)
        int iArguments = lua_gettop(luaVM) - 1;
        
        // Call the global function
        if (CLuaCFunctions::CallGlobalFunction(strFunctionName, luaVM, iArguments))
        {
            // Return values are already on the stack
            // Return all values that were pushed
            return lua_gettop(luaVM) - 1;  // Subtract the function name argument
        }
        else
        {
            m_pScriptDebugging->LogError(luaVM, "Global function '%s' not found or failed to call", strFunctionName.c_str());
        }
    }
    else
    {
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());
    }

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaGlobalFunctionDefs::HasGlobalFunction(lua_State* luaVM)
{
    // hasGlobalFunction(string name)
    SString strFunctionName;
    
    CScriptArgReader argStream(luaVM);
    argStream.ReadString(strFunctionName);

    if (!argStream.HasErrors())
    {
        bool bExists = CLuaCFunctions::HasGlobalFunction(strFunctionName);
        lua_pushboolean(luaVM, bExists);
        return 1;
    }

    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaGlobalFunctionDefs::RemoveGlobalFunction(lua_State* luaVM)
{
    // removeGlobalFunction(string name)
    SString strFunctionName;
    
    CScriptArgReader argStream(luaVM);
    argStream.ReadString(strFunctionName);

    if (!argStream.HasErrors())
    {
        if (CLuaCFunctions::HasGlobalFunction(strFunctionName))
        {
            CLuaCFunctions::RemoveGlobalFunction(strFunctionName);
            lua_pushboolean(luaVM, true);
            return 1;
        }
        else
        {
            m_pScriptDebugging->LogWarning(luaVM, "Global function '%s' does not exist", strFunctionName.c_str());
        }
    }

    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaGlobalFunctionDefs::GetGlobalFunctions(lua_State* luaVM)
{
    // getGlobalFunctions() - returns a table with all global function names
    
    lua_newtable(luaVM);
    
    // This would need to be implemented in CLuaCFunctions to iterate through ms_GlobalFunctions
    // For now, return empty table
    
    return 1;
}
