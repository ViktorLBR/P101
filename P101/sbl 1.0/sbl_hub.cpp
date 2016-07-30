#include "stdafx.h"
#include "sbl_hub.h"

using namespace std;


// -----
// Destructeur & Constructeur
// -----

sblHub::sblHub()
{
	//bd_nom_element = *(new map<string, pElement>);
	//bd_element = *(new vSElement);
	//map<string, pElement> bd_nom_element;// = (new map<string, pElement>();
	//bd_nom_element->emplace("null", NULL);
	//if (hub_lua != NULL)
		//delete this;
}

sblHub::~sblHub()
{
	for each (mappNadrElement selem in bd_element)
		delete selem.second;
	for each (mappSpElement elem in bd_nom_element)
		delete elem.second;
	delete cible; // Mieux vaut deux fois qu'une
}


// -----
// Utilitaires
// -----

sblAdr sblHub::nextFreeNadr()
{
	sblAdr nadr = 1; // TODO
	while (true)
	{
		if (bd_element.count(nadr) == 0)
			return nadr;
		nadr++;
	}
}


// -----
// Fonctions lua
// -----

int sblHub::charger(lua_State * L)
{
	sblAdr nadr = lua_tonumber(L, 1);
	cible = bd_element.find(nadr)->second;
	nadr_cible = nadr;
	return 0;
}

int sblHub::fermer(lua_State * L)
{
	cible = NULL;
	nadr_cible = NULL;
	return 0;
}

int sblHub::getcible(lua_State * L)
{
	sblAdr nadr = nadr_cible;
	lua_pushnumber(L, nadr);
	return 1;
}

int sblHub::set(lua_State * L)
{
	string nom = lua_tostring(L, 1);
	if (cible != NULL)
		return cible->set(nom, L);
	return 0;
}

int sblHub::get(lua_State * L)
{
	string nom = lua_tostring(L, 1);
	if (cible != NULL)
		return cible->get(nom, L);
	return 0;
}

int sblHub::exec(lua_State * L)
{
	string nom = lua_tostring(L, 1);
	if (cible != NULL)
		return cible->exec(nom, L);
	return 0;
}

int sblHub::create(lua_State * L)
{
	// Préparation
	sblAdr nadr = nextFreeNadr();
	string nom = lua_tostring(L, 1);

	// Récupération de l'élément
	pElement buffer = bd_nom_element.at(nom)->Copie();
	if (buffer != NULL)
		bd_element.emplace(nadr, buffer);

	// Retour du nadr
	lua_pushnumber(L, nadr);
	return 1;
}


// -----
// Gestion librairie
// -----

void sblHub::lib_ajouter(string nom, pElement pelement)
{
	bd_nom_element.emplace(nom, pelement->Copie());
}