#include "stdafx.h"
#include "gen_boost.h"

using namespace gen;
/*
template<class T>
int gen::Executeur<T>::exec(string nfonc, lua_State * L)
{
	if (nfonc == "pushSlot")
	{
		sbl::sbl_push(L, push(lua_tostring(L, 2), convert<T>(hub_lua->getElement(lua_tonumber(L, 3)))));
		return 1;
	}
	if (nfonc == "popSlot")
	{
		sbl::sbl_push(L, pop(lua_tostring(L, 2)));
		return 1;
	}

	return sblElement::exec(nfonc, L);
}*/