#include "stdafx.h"
#include "sbl_main.h"

sblHub * hub_lua = NULL;
EnvLua * env = NULL;

lua_State * getEnv()
{
	return env->getEnv();
}