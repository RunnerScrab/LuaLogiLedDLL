// LuaLogiLed.cpp : Defines the exported functions for the DLL application.
//
#include "LogitechLEDLib.h"

extern "C"
{

#include <stdio.h>
#include <stdlib.h>

#include "include\lua.h"
#include "include\lauxlib.h"
#include "include\lualib.h"

	static int LogiLedInitWrapper(lua_State* L)
	{
		int retval = !!LogiLedInit();
		lua_pushnumber(L, retval);
		return 1;
	}

	static int LogiLedShutdownWrapper(lua_State* L)
	{
		LogiLedShutdown();
		return 0;
	}

	static int LogiLedSetTargetDeviceWrapper(lua_State* L)
	{
		int arg = luaL_checkinteger(L, 1);
		int retval = !!LogiLedSetTargetDevice(arg);
		lua_pushnumber(L, retval);
		return 1;
	}

	static int LogiLedSetLightingWrapper(lua_State* L)
	{
		int r = luaL_checkinteger(L, 1);
		int g = luaL_checkinteger(L, 2);
		int b = luaL_checkinteger(L, 3);

		int retval = !!LogiLedSetLighting(r, g, b);
		lua_pushnumber(L, retval);
		return 1;
	}

	static int LogiLedSaveCurrentLightingWrapper(lua_State* L)
	{
		int retval = LogiLedSaveCurrentLighting();
		lua_pushnumber(L, retval);
		return 1;
	}

	static int LogiLedRestoreLightingWrapper(lua_State* L)
	{
		int retval = LogiLedRestoreLighting();
		lua_pushnumber(L, retval);
		return 1;
	}

	static int LogiLedFlashLightingWrapper(lua_State* L)
	{
		int r = luaL_checkinteger(L, 1);
		int g = luaL_checkinteger(L, 2);
		int b = luaL_checkinteger(L, 3);
		int ms_duration = luaL_checkinteger(L, 4);
		int ms_interval = luaL_checkinteger(L, 5);
		int retval = LogiLedFlashLighting(r, g, b, ms_duration, ms_interval);
		lua_pushnumber(L, retval);
		return 1;
	}

	static const luaL_reg LogiLedFuncTable[] =
	{
		{"Init", LogiLedInitWrapper},
		{"Shutdown", LogiLedShutdownWrapper},
		{"SetTargetDevice", LogiLedSetTargetDeviceWrapper},
		{"SetLighting", LogiLedSetLightingWrapper},
		{"SaveCurrentLighting", LogiLedSaveCurrentLightingWrapper},
		{"RestoreLighting", LogiLedRestoreLightingWrapper},
		{"FlashLighting", LogiLedFlashLightingWrapper},
		{NULL, NULL}
	};

	__declspec(dllexport) int LoadLedLib(lua_State *L)
	{
		luaL_openlib(L, "LogiLed", LogiLedFuncTable, 0);
		return 1;
	}
}