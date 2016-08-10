#include "stdafx.h"

using namespace sbl;

#ifndef SBL_HUB
#define SBL_HUB
// -----
// Classe
// -----

class sblHub
{
public:
	enum mode_callback{ CPP, LUA } mode_call;

	// -----
	// Destructeur & Constructeur
	// -----
	sblHub(); // Une seule instance !!!
	~sblHub(); // Détruit les Eléments !!!


	// -----
	// Fonctions lua
	// -----
	int charger(lua_State * L);
	void charger(sblAdr nadr); // C++

	int fermer(lua_State * L);
	void fermer(void); // C++

	int getcible(lua_State * L);
	pElement getcible(void); // C++
	
	int set(lua_State * L);
	
	int get(lua_State * L);
	
	int exec(lua_State * L);

	int getnom(lua_State * L);
	sblElement * getnom(string nom); // C++
	
	int create(lua_State * L);
	sblAdr create(string nom); // C++


	// -----
	// Gestion librairie
	// -----
	void lib_ajouter(string nom, pElement pelement);

	void ajouter_element(pElement pelement);

	sblElement * getElement(sblAdr nadr)
	{
		return bd_element.at(nadr);
	}

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