/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *               (Shared logic for modifications)
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/shared_logic/lua/CLuaFunctions.cpp
 *  PURPOSE:     Lua functions class
 *
 *****************************************************************************/

#include <StdInc.h>

static std::vector<CLuaCFunction*>             m_sFunctions;
static std::map<lua_CFunction, CLuaCFunction*> ms_Functions;
static void*                                   ms_pFunctionPtrLow = (void*)0xffffffff;
static void*                                   ms_pFunctionPtrHigh = 0;
CFastHashMap<SString, CLuaCFunctions::SGlobalFunction*> CLuaCFunctions::ms_GlobalFunctions;

CLuaCFunction::CLuaCFunction(const char* szName, lua_CFunction f, bool bRestricted)
{
    m_strName = szName;
    m_Function = f;
    m_bRestricted = bRestricted;
}

CLuaCFunction* CLuaCFunctions::AddFunction(const char* szName, lua_CFunction f, bool bRestricted)
{
    ms_pFunctionPtrLow = std::min<void*>(ms_pFunctionPtrLow, (void*)f);
    ms_pFunctionPtrHigh = std::max<void*>(ms_pFunctionPtrHigh, (void*)f);

    // See if we already have it added. Eventually just return it instead of adding it twice
    CLuaCFunction* pFunction = GetFunction(szName, f);
    if (pFunction)
        return pFunction;

    // Create it, add to list and return
    pFunction = new CLuaCFunction(szName, f, bRestricted);
    m_sFunctions.push_back(pFunction);
    MapSet(ms_Functions, f, pFunction);
    return pFunction;
}

CLuaCFunction* CLuaCFunctions::GetFunction(const char* szName, lua_CFunction f)
{
    // Grab a function of the given name and type
    std::vector<CLuaCFunction*>::const_iterator iter = m_sFunctions.begin();
    for (; iter != m_sFunctions.end(); iter++)
    {
        if ((*iter)->GetFunctionAddress() == f && strcmp((*iter)->GetFunctionName(), szName) == 0)
        {
            return *iter;
        }
    }

    return NULL;
}

CLuaCFunction* CLuaCFunctions::GetFunction(const char* szName)
{
    // Grab a function of the given name and type
    std::vector<CLuaCFunction*>::const_iterator iter = m_sFunctions.begin();
    for (; iter != m_sFunctions.end(); iter++)
    {
        if (strcmp((*iter)->GetFunctionName(), szName) == 0)
        {
            return *iter;
        }
    }

    return NULL;
}

CLuaCFunction* CLuaCFunctions::GetFunction(lua_CFunction f)
{
    // Quick cull of unknown pointer range
    if (IsNotFunction(f))
        return NULL;

    return MapFindRef(ms_Functions, f);
}

const char* CLuaCFunctions::GetFunctionName(lua_CFunction f, bool& bRestricted)
{
    // Return the function name of the given C address
    std::vector<CLuaCFunction*>::const_iterator iter = m_sFunctions.begin();
    for (; iter != m_sFunctions.end(); iter++)
    {
        if ((*iter)->GetFunctionAddress() == f)
        {
            bRestricted = (*iter)->IsRestricted();
            return (*iter)->GetFunctionName();
        }
    }

    bRestricted = false;
    return NULL;
}

//
// Returns true if definitely not a registered function.
// Note: Returning false does not mean it is a registered function
//
bool CLuaCFunctions::IsNotFunction(lua_CFunction f)
{
    // Return true if unknown pointer range
    return (f < ms_pFunctionPtrLow || f > ms_pFunctionPtrHigh);
}

bool CLuaCFunctions::IsRestricted(const char* szName)
{
    // Grab a function of the given name and type
    std::vector<CLuaCFunction*>::const_iterator iter = m_sFunctions.begin();
    for (; iter != m_sFunctions.end(); iter++)
    {
        if (strcmp((*iter)->GetFunctionName(), szName) == 0)
        {
            return (*iter)->IsRestricted();
        }
    }

    // Not restricted by MTA atleast
    return false;
}

void CLuaCFunctions::RegisterFunctionsWithVM(lua_State* luaVM)
{
    // Register all our functions to a lua VM
    std::vector<CLuaCFunction*>::const_iterator iter = m_sFunctions.begin();
    for (; iter != m_sFunctions.end(); iter++)
    {
        lua_pushstring(luaVM, (*iter)->GetFunctionName());
        lua_pushcclosure(luaVM, (*iter)->GetFunctionAddress(), 1);
        lua_setglobal(luaVM, (*iter)->GetFunctionName());
    }
}

void CLuaCFunctions::RemoveAllFunctions()
{
    for (CLuaCFunction* luaCFunction : m_sFunctions)
    {
        delete luaCFunction;
    }

    m_sFunctions.clear();
    ClearGlobalFunctions();
}

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
