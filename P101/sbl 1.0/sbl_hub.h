#include "stdafx.h"

#ifndef SBL_HUB
#define SBL_HUB

// -----
// Classe
// -----

class sblHub
{
public:


	// -----
	// Destructeur & Constructeur
	// -----
	sblHub(); // Une seule instance !!!
	~sblHub(); // Détruit les Eléments !!!


	// -----
	// Fonctions lua
	// -----
	int charger(lua_State * L);
	int fermer(lua_State * L);
	int getcible(lua_State * L);
	int set(lua_State * L);
	int get(lua_State * L);
	int exec(lua_State * L);
	int create(lua_State * L);


	// -----
	// Gestion librairie
	// -----
	void lib_ajouter(string nom, pElement pelement);


protected:
	sblAdr nadr_cible;
	pElement cible; // Element sur lequel s'appliquent set(), get() et exec()
	map<string, pElement > bd_nom_element;
	map<sblAdr, pElement> bd_element;
	
	// -----
	// Utilitaires
	// -----
	sblAdr nextFreeNadr();
};

#endif