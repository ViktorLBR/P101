#include "stdafx.h"

#ifndef SBL_INT_HUB
#define SBL_INT_HUB

using namespace std;
using namespace sbl;

// -----
// Interface
// -----

// Libère sblHub::cible
int fermer(lua_State * L);

// Charge sblHub::cible avec un nadr
int charger(lua_State * L);

// Retourne sblHub::cible nadr
int getcible(lua_State * L);

// Exécute cible::set()
int set(lua_State * L);

// Exécute cible::get()
int get(lua_State * L);

// Exécute cible::exec()
int exec(lua_State * L);

// Crée un élément (et retourne un nadr)
int create(lua_State * L);

// Enregistre les fonctions d'interface
void ChargerInterfaceHub(lua_State * L);

#endif