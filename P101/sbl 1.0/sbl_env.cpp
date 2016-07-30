#include "stdafx.h"
#include "sbl_main.h"

using namespace std;


EnvLua::EnvLua()
{
	Init();
	ChargerInterfaceHub(etat);
}

EnvLua::EnvLua(lua_State * petat)
{
	etat = petat;
	ChargerInterfaceHub(etat);
}