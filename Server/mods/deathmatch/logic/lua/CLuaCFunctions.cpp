/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/lua/CLuaCFunctions.cpp
 *  PURPOSE:     Lua C-function extension class
 *
 *  Multi Theft Auto is available from https://www.multitheftauto.com/
 *
 *****************************************************************************/

#include "StdInc.h"
#include "CLuaCFunctions.h"

CFastHashMap<lua_CFunction, CLuaCFunction*>             CLuaCFunctions::ms_Functions;
CFastHashMap<SString, CLuaCFunction*>                   CLuaCFunctions::ms_FunctionsByName;
void*                                                   CLuaCFunctions::ms_pFunctionPtrLow = (void*)0xffffffff;
void*                                                   CLuaCFunctions::ms_pFunctionPtrHigh = 0;
CFastHashMap<SString, CLuaCFunctions::SGlobalFunction*> CLuaCFunctions::ms_GlobalFunctions;

// CFastHashMap helpers
static lua_CFunction GetEmptyMapKey(lua_CFunction*)
{
    return (lua_CFunction)0x00000000;
}
static lua_CFunction GetDeletedMapKey(lua_CFunction*)
{
    return (lua_CFunction)0xFFFFFFFF;
}

CLuaCFunction::CLuaCFunction(const char* szName, lua_CFunction f, bool bRestricted)
{
    m_strName = szName ? szName : "";
    m_Function = f;
    m_bRestricted = bRestricted;
}

CLuaCFunctions::CLuaCFunctions()
{
}

CLuaCFunctions::~CLuaCFunctions()
{
    RemoveAllFunctions();
}

CLuaCFunction* CLuaCFunctions::AddFunction(const char* szName, lua_CFunction f, bool bRestricted)
{
    ms_pFunctionPtrLow = std::min<void*>(ms_pFunctionPtrLow, (void*)f);
    ms_pFunctionPtrHigh = std::max<void*>(ms_pFunctionPtrHigh, (void*)f);

    // Already have a function by this name?
    CLuaCFunction* pFunction = GetFunction(szName);
    if (pFunction)
        return pFunction;

    // Already have a function by this address?
    pFunction = GetFunction(f);
    if (!pFunction)
    {
        pFunction = new CLuaCFunction(szName, f, bRestricted);
        ms_Functions[f] = pFunction;
    }
    ms_FunctionsByName[szName] = pFunction;
    return pFunction;
}

void CLuaCFunctions::RemoveFunction(const SString& strName)
{
    CFastHashMap<SString, CLuaCFunction*>::iterator iter = ms_FunctionsByName.find(strName);
    if (iter != ms_FunctionsByName.end())
    {
        ms_Functions.erase(iter->second->GetAddress());
        ms_FunctionsByName.erase(iter);
        delete iter->second;
    }
}

CLuaCFunction* CLuaCFunctions::GetFunction(lua_CFunction f)
{
    // Quick cull of unknown pointer range
    if (reinterpret_cast<void*>(f) < ms_pFunctionPtrLow || reinterpret_cast<void*>(f) > ms_pFunctionPtrHigh)
        return NULL;

    CFastHashMap<lua_CFunction, CLuaCFunction*>::iterator it;
    it = ms_Functions.find(f);
    if (it == ms_Functions.end())
        return NULL;

    return it->second;
}

CLuaCFunction* CLuaCFunctions::GetFunction(const char* szName)
{
    CFastHashMap<SString, CLuaCFunction*>::iterator it;
    it = ms_FunctionsByName.find(szName);
    if (it == ms_FunctionsByName.end())
        return NULL;

    return it->second;
}

//
// Returns true if definitely not a registered function.
// Note: Returning false does not necessarily mean it is a registered function
//
bool CLuaCFunctions::IsNotFunction(lua_CFunction f)
{
    // Return true if unknown pointer range
    return (reinterpret_cast<void*>(f) < ms_pFunctionPtrLow || reinterpret_cast<void*>(f) > ms_pFunctionPtrHigh);
}

void CLuaCFunctions::RegisterFunctionsWithVM(lua_State* luaVM)
{
    // Register all our functions to a lua VM
    CFastHashMap<SString, CLuaCFunction*>::iterator it;
    for (it = ms_FunctionsByName.begin(); it != ms_FunctionsByName.end(); ++it)
    {
        lua_pushstring(luaVM, it->first.c_str());
        lua_pushcclosure(luaVM, it->second->GetAddress(), 1);
        lua_setglobal(luaVM, it->first.c_str());
    }
}

void CLuaCFunctions::RemoveAllFunctions()
{
    // Delete all functions
    CFastHashMap<lua_CFunction, CLuaCFunction*>::iterator it;
    for (it = ms_Functions.begin(); it != ms_Functions.end(); ++it)
    {
        delete it->second;
    }
    ms_Functions.clear();
    ms_FunctionsByName.clear();
}

//
// Global function system implementation
//

// Register a Lua function as globally accessible across all resources
void CLuaCFunctions::RegisterGlobalFunction(const SString& strName, lua_State* luaVM)
{
    // Check if function already exists
    if (HasGlobalFunction(strName))
    {
        RemoveGlobalFunction(strName);
    }

    // Ensure the value at the top of the stack is a function
    if (!lua_isfunction(luaVM, -1))
    {
        return;
    }

    // Create a reference to the function in the Lua registry
    int iRef = luaL_ref(luaVM, LUA_REGISTRYINDEX);

    // Store the global function
    SGlobalFunction* pGlobalFunc = new SGlobalFunction();
    pGlobalFunc->iLuaRef = iRef;
    pGlobalFunc->pSourceVM = luaVM;
    pGlobalFunc->strName = strName;

    ms_GlobalFunctions[strName] = pGlobalFunc;
}

// Call a globally registered function from any VM
bool CLuaCFunctions::CallGlobalFunction(const SString& strName, lua_State* luaVM, int iArguments)
{
    // Find the global function
    CFastHashMap<SString, SGlobalFunction*>::iterator it = ms_GlobalFunctions.find(strName);
    if (it == ms_GlobalFunctions.end())
    {
        return false;
    }

    SGlobalFunction* pGlobalFunc = it->second;

    // Get the function from the registry of the source VM
    lua_rawgeti(pGlobalFunc->pSourceVM, LUA_REGISTRYINDEX, pGlobalFunc->iLuaRef);

    // If calling from a different VM, we need to transfer arguments
    if (luaVM != pGlobalFunc->pSourceVM)
    {
        // Transfer arguments from calling VM to source VM
        for (int i = -iArguments; i < 0; i++)
        {
            // Copy each argument (this is simplified - proper implementation needs type checking)
            if (lua_isnumber(luaVM, i))
            {
                lua_pushnumber(pGlobalFunc->pSourceVM, lua_tonumber(luaVM, i));
            }
            else if (lua_isstring(luaVM, i))
            {
                lua_pushstring(pGlobalFunc->pSourceVM, lua_tostring(luaVM, i));
            }
            else if (lua_isboolean(luaVM, i))
            {
                lua_pushboolean(pGlobalFunc->pSourceVM, lua_toboolean(luaVM, i));
            }
            else if (lua_isnil(luaVM, i))
            {
                lua_pushnil(pGlobalFunc->pSourceVM);
            }
            // Add more type transfers as needed
        }
    }

    // Call the function
    int iResult = lua_pcall(pGlobalFunc->pSourceVM, iArguments, LUA_MULTRET, 0);

    if (iResult != 0)
    {
        // Error occurred
        const char* szError = lua_tostring(pGlobalFunc->pSourceVM, -1);
        lua_pop(pGlobalFunc->pSourceVM, 1);
        return false;
    }

    // Transfer return values back if needed
    if (luaVM != pGlobalFunc->pSourceVM)
    {
        int iReturnValues = lua_gettop(pGlobalFunc->pSourceVM);
        for (int i = 1; i <= iReturnValues; i++)
        {
            if (lua_isnumber(pGlobalFunc->pSourceVM, i))
            {
                lua_pushnumber(luaVM, lua_tonumber(pGlobalFunc->pSourceVM, i));
            }
            else if (lua_isstring(pGlobalFunc->pSourceVM, i))
            {
                lua_pushstring(luaVM, lua_tostring(pGlobalFunc->pSourceVM, i));
            }
            else if (lua_isboolean(pGlobalFunc->pSourceVM, i))
            {
                lua_pushboolean(luaVM, lua_toboolean(pGlobalFunc->pSourceVM, i));
            }
            else if (lua_isnil(pGlobalFunc->pSourceVM, i))
            {
                lua_pushnil(luaVM);
            }
        }
        lua_pop(pGlobalFunc->pSourceVM, iReturnValues);
    }

    return true;
}

// Check if a global function exists
bool CLuaCFunctions::HasGlobalFunction(const SString& strName)
{
    return ms_GlobalFunctions.find(strName) != ms_GlobalFunctions.end();
}

// Remove a global function
void CLuaCFunctions::RemoveGlobalFunction(const SString& strName)
{
    CFastHashMap<SString, SGlobalFunction*>::iterator it = ms_GlobalFunctions.find(strName);
    if (it != ms_GlobalFunctions.end())
    {
        SGlobalFunction* pGlobalFunc = it->second;
        
        // Release the Lua reference
        luaL_unref(pGlobalFunc->pSourceVM, LUA_REGISTRYINDEX, pGlobalFunc->iLuaRef);
        
        delete pGlobalFunc;
        ms_GlobalFunctions.erase(it);
    }
}

// Clear all global functions
void CLuaCFunctions::ClearGlobalFunctions()
{
    CFastHashMap<SString, SGlobalFunction*>::iterator it;
    for (it = ms_GlobalFunctions.begin(); it != ms_GlobalFunctions.end(); ++it)
    {
        SGlobalFunction* pGlobalFunc = it->second;
        luaL_unref(pGlobalFunc->pSourceVM, LUA_REGISTRYINDEX, pGlobalFunc->iLuaRef);
        delete pGlobalFunc;
    }
    ms_GlobalFunctions.clear();
}
