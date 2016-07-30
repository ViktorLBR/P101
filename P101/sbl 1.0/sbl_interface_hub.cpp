#include "stdafx.h"
#include "sbl_interface_hub.h"

// -----
// Interface
// -----

// Lib�re sblHub::cible
int fermer(lua_State * L)
{
	return hub_lua->fermer(L);
}

// Charge sblHub::cible avec un nadr
int charger(lua_State * L)
{
	return hub_lua->charger(L);
}

// Retourne sblHub::cible nadr
int getcible(lua_State * L)
{
	return hub_lua->getcible(L);
}

// Ex�cute cible::set()
int set(lua_State * L)
{
	return hub_lua->set(L);
}

// Ex�cute cible::get()
int get(lua_State * L)
{
	return hub_lua->get(L);
}

// Ex�cute cible::exec()
int exec(lua_State * L)
{
	return hub_lua->exec(L);
}

// Cr�e un �l�ment (et retourne un nadr)
int create(lua_State * L)
{
	return hub_lua->create(L);
}

// Enregistre les fonctions d'interface
void ChargerInterfaceHub(lua_State * L)
{
	lua_register(L, "sbl_charger", charger);
	lua_register(L, "sbl_fermer", fermer);
	lua_register(L, "sbl_getcible", getcible);
	lua_register(L, "sbl_set", set);
	lua_register(L, "sbl_get", get);
	lua_register(L, "sbl_exec", exec);
	lua_register(L, "sbl_create", create);
}