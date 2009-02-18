
#include "common.h"

// interface header
#include "LuaDouble.h"

// system headers
#include <math.h>
#include <string>
using std::string;

// local headers
#include "LuaInclude.h"
#include "LuaHashString.h"


const char* LuaDouble::metaName = "Double";


/******************************************************************************/
/******************************************************************************/

bool LuaDouble::IsDouble(lua_State* L, int index)
{
	return (lua_getuserdataextra(L, index) == metaName);
}


double* LuaDouble::TestDouble(lua_State* L, int index)
{
	if (lua_getuserdataextra(L, index) != metaName) {
		return NULL;
	}
	double* doublePtr = (double*)lua_touserdata(L, index);
	return doublePtr;
}


double* LuaDouble::TestNumber(lua_State* L, int index)
{
	static double value = 0.0f;
	if (lua_israwnumber(L, index)) {
		value = (double)lua_tonumber(L, 1);
		return &value;
	}
	if (lua_getuserdataextra(L, index) != metaName) {
		return NULL;
	}
	double* doublePtr = (double*)lua_touserdata(L, index);
	return doublePtr;
}


double LuaDouble::CheckDouble(lua_State* L, int index)
{
	if (lua_getuserdataextra(L, index) != LuaDouble::metaName) {
		luaL_argerror(L, index, "expected a Double");
	}
	const double* doublePtr = (double*)lua_touserdata(L, index);
	return *doublePtr;
}


double LuaDouble::CheckNumber(lua_State* L, int index)
{
	if (lua_israwnumber(L, index)) {
		return (double)lua_tonumber(L, index);
	}
	return CheckDouble(L, index);
}


/******************************************************************************/
/******************************************************************************/

int LuaDouble::MetaIndex(lua_State* L)
{
	const double d1 = CheckDouble(L, 1);
	const string key = luaL_checkstring(L, 2);
	if (key == "number") {
		lua_pushnumber(L, (float)d1);
		return 1;
	}
	else if (key == "string") {
		return MetaToString(L);
	}
/* FIXME -- require _ISOC99_SOURCE
	else if (key == "class") {
		switch (fpclassify(d1)) {
			case FP_NAN:       { lua_pushliteral(L, "NAN");       }
			case FP_INFINITE:  { lua_pushliteral(L, "INFINITE");  }
			case FP_ZERO:      { lua_pushliteral(L, "ZERO");      }
			case FP_SUBNORMAL: { lua_pushliteral(L, "SUBNORMAL"); }
			case FP_NORMAL:    { lua_pushliteral(L, "NORMAL");    }
			default:           { lua_pushliteral(L, "UNKNOWN");   }
		}
		return 1;
	}
	else if (key == "isnan") {
		lua_pushboolean(L, isnan(d1));
		return 1;
	}
	else if (key == "isfinite") {
		lua_pushboolean(L, isfinite(d1));
		return 1;
	}
	else if (key == "isinf") {
		lua_pushboolean(L, isinf(d1));
		return 1;
	}
	else if (key == "isnormal") {
		lua_pushboolean(L, isnormal(d1));
		return 1;
	}
*/
	return 0;
}


int LuaDouble::MetaToString(lua_State* L)
{
	const double d1 = CheckDouble(L, 1);
	char buf[128];
	snprintf(buf, sizeof(buf), "%.14g", d1);
	lua_pushstring(L, buf);
	return 1;
}


int LuaDouble::MetaADD(lua_State* L)
{
	const double d1 = CheckNumber(L, 1);
	const double d2 = CheckNumber(L, 2);
	PushDouble(L, d1 + d2);
	return 1;
}


int LuaDouble::MetaSUB(lua_State* L)
{
	const double d1 = CheckNumber(L, 1);
	const double d2 = CheckNumber(L, 2);
	PushDouble(L, d1 - d2);
	return 1;
}


int LuaDouble::MetaMUL(lua_State* L)
{
	const double d1 = CheckNumber(L, 1);
	const double d2 = CheckNumber(L, 2);
	PushDouble(L, d1 * d2);
	return 1;
}


int LuaDouble::MetaDIV(lua_State* L)
{
	const double d1 = CheckNumber(L, 1);
	const double d2 = CheckNumber(L, 2);
	PushDouble(L, d1 / d2);
	return 1;
}


int LuaDouble::MetaMOD(lua_State* L)
{
	const double d1 = CheckNumber(L, 1);
	const double d2 = CheckNumber(L, 2);
	PushDouble(L, fmod(d1, d2));
	return 1;
}


int LuaDouble::MetaPOW(lua_State* L)
{
	const double d1 = CheckNumber(L, 1);
	const double d2 = CheckNumber(L, 2);
	PushDouble(L, pow(d1, d2));
	return 1;
}


int LuaDouble::MetaUNM(lua_State* L)
{
	const double d1 = CheckNumber(L, 1);
	PushDouble(L, -d1);
	return 1;
}


int LuaDouble::MetaEQ(lua_State* L)
{
	const double d1 = CheckNumber(L, 1);
	const double d2 = CheckNumber(L, 2);
	lua_pushboolean(L, d1 == d2);
	return 1;
}


int LuaDouble::MetaLT(lua_State* L)
{
	const double d1 = CheckNumber(L, 1);
	const double d2 = CheckNumber(L, 2);
	lua_pushboolean(L, d1 < d2);
	return 1;
}


int LuaDouble::MetaLE(lua_State* L)
{
	const double d1 = CheckNumber(L, 1);
	const double d2 = CheckNumber(L, 2);
	lua_pushboolean(L, d1 <= d2);
	return 1;
}


/******************************************************************************/
/******************************************************************************/

bool LuaDouble::CreateMetatable(lua_State* L)
{
	luaL_newmetatable(L, metaName);

	HSTR_PUSH_CFUNC(L, "__index",    MetaIndex);
	HSTR_PUSH_CFUNC(L, "__tostring", MetaToString);

	HSTR_PUSH_CFUNC(L, "__add",  MetaADD);
	HSTR_PUSH_CFUNC(L, "__sub",  MetaSUB);
	HSTR_PUSH_CFUNC(L, "__mul",  MetaMUL);
	HSTR_PUSH_CFUNC(L, "__div",  MetaDIV);
	HSTR_PUSH_CFUNC(L, "__mod",  MetaMOD);
	HSTR_PUSH_CFUNC(L, "__pow",  MetaPOW);
	HSTR_PUSH_CFUNC(L, "__unm",  MetaUNM);
	HSTR_PUSH_CFUNC(L, "__eq",   MetaEQ);
	HSTR_PUSH_CFUNC(L, "__lt",   MetaLT);
	HSTR_PUSH_CFUNC(L, "__le",   MetaLE);

	HSTR_PUSH_STRING(L, "__metatable", "no access");

	lua_pop(L, 1);

	return true;
}

/******************************************************************************/
/******************************************************************************/

int LuaDouble::IsDouble(lua_State* L)
{
	lua_pushboolean(L, lua_getuserdataextra(L, 1) == metaName);
	return 1;
}


int LuaDouble::CreateDouble(lua_State* L)
{
	double value = 0.0f;
	if (lua_israwnumber(L, 1)) {
		value = (double)lua_tonumber(L, 1);
	}
	else if (lua_israwstring(L, 1)) {
		const char* start = lua_tostring(L, 1);
		char* end;
		value = strtod(start, &end);
		if (start == end) {
			luaL_argerror(L, 1, "invalid numeric string");
		}
	}
	else {
		value = CheckDouble(L, 1);
	}

	double* doublePtr = (double*)lua_newuserdata(L, sizeof(double));
	*doublePtr = value;

	lua_setuserdataextra(L, -1, (void*)metaName);
	luaL_getmetatable(L, metaName);
	lua_setmetatable(L, -2);

	return 1;
}


void LuaDouble::PushDouble(lua_State* L, double value)
{
	double* doublePtr = (double*)lua_newuserdata(L, sizeof(double));
	*doublePtr = value;

	lua_setuserdataextra(L, -1, (void*)metaName);
	luaL_getmetatable(L, metaName);
	lua_setmetatable(L, -2);
}


/******************************************************************************/
/******************************************************************************/

bool LuaDouble::PushEntries(lua_State* L)
{
	CreateMetatable(L);

	HSTR_PUSH_CFUNC(L, "double", CreateDouble);
	HSTR_PUSH_CFUNC(L, "isdouble", IsDouble);

	return true;
}


/******************************************************************************/
/******************************************************************************/