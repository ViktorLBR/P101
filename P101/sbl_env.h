#include "stdafx.h"

#ifndef P101_SBL_MAIN
#define P101_SBL_MAIN

using namespace std;
using namespace sbl;


class EnvLua
{

public:
	EnvLua();
	EnvLua(lua_State * etat);
	~EnvLua() { lua_close(etat); }

	void Exec(string fichier)
	{
		luaL_dofile(etat, fichier.c_str());
	}

	void ExecS(string cmd)
	{
		luaL_dostring(etat, cmd.c_str());
	}

	lua_State * getEnv()
	{
		return etat;
	}

	void Enregistrer(string nom, lua_CFunction fonction)
	{
		lua_register(etat, nom.c_str(), fonction);
	}

protected:
	lua_State * etat;

	void Init()
	{
		etat = luaL_newstate();

		static const luaL_Reg lualibs[] =
		{
			{ "base", luaopen_base },
			{ NULL, NULL }
		};

		const luaL_Reg *lib = lualibs;
		for (; lib->func != NULL; lib++)
		{
			lib->func(etat);
			lua_settop(etat, 0);
		}
	}
};

extern EnvLua * env;

#endif