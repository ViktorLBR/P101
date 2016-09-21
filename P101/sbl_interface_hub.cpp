#include "stdafx.h"
#include "sbl_interface_hub.h"

// -----
// Interface
// -----

// Libère sblHub::cible
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

// Exécute cible::set()
int set(lua_State * L)
{
	return hub_lua->set(L);
}

int print(lua_State * L)
{
	cout << "lua_print> " << lua_tostring(L, 1) << endl;
	return 0;
}

// Exécute cible::get()
int get(lua_State * L)
{
	return hub_lua->get(L);
}

// Exécute cible::exec()
int exec(lua_State * L)
{
	return hub_lua->exec(L);
}

// Crée un élément (et retourne un nadr)
int create(lua_State * L)
{
	return hub_lua->create(L);
}

// Cherche par nom
int getnom(lua_State * L)
{
	return hub_lua->getnom(L);
}

// Enregistre les fonctions d'interface
void ChargerInterfaceHub(lua_State * L)
{
	// Bleurbleblure
	lua_register(L, "sbl_charger", charger);
	lua_register(L, "sbl_fermer", fermer);
	lua_register(L, "sbl_getcible", getcible);
	lua_register(L, "sbl_set", set);
	lua_register(L, "sbl_get", get);
	lua_register(L, "sbl_exec", exec);
	lua_register(L, "sbl_create", create);
	lua_register(L, "sbl_getnom", getnom);
	lua_register(L, "sbl_print", print);
}