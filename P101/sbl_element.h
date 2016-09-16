#include "stdafx.h"

#ifndef SBL_ELEMENT
#define SBL_ELEMENT

using namespace std;
using namespace sbl;

class sblElement
{
public:
	string nom;

	virtual int set(string nvar, lua_State * L)
	{
		if (nvar == "nom")
		{
			nom = lua_tostring(L, 2);
			return 0;
		}
		return 0;
	}

	virtual int get(string nvar, lua_State * L)
	{
		if (nvar == "nom")
		{
			lua_pushstring(L, nom.c_str());
			return 1;
		}
		return 0;
	}

	virtual int exec(string nfonc, lua_State * L)
	{
		return 0;
	}

	void setNadr(sblAdr nadr) { this->nadr = nadr; }
	sblAdr getNadr() { return nadr; }

	virtual sblElement * Copie()
	{
		sblElement * p = new sblElement();

		HCopie(p);

		return p;
	}

protected:
	sblAdr nadr;

	virtual void HCopie(sblElement * p)
	{
		p->nom = nom;
	}
};

#include "sbl_boost.h"

class sblCElement : public sblElement
{
public:

	bool isFonction(string nomc);
	virtual bool enregFonction(string nomc, string nomlua, int arg)
	{
		if (isFonction(nomc))
			return false;
		map_fonctions.emplace(nomc, *(new lua_Callback(nomlua, arg)));
		return true;
	}
	template<class Args>bool execFonction(string nomc, Args args)
	{
		if (isFonction(nomc))
			return map_fonctions.at(nomc).exec(L_gen, this, args);
		return false;
	}
	bool execFonction(string nomc)
	{
		if (isFonction(nomc))
			return map_fonctions.at(nomc).exec(getEnv(), this, 0);
		return false;
	}

	virtual int set(string var, lua_State * L);
	virtual int get(string var, lua_State * L);
	virtual int exec(string nfonc, lua_State * L);
	virtual sblElement * sblCElement::Copie();

protected:
	map<string, sbl::lua_Callback> map_fonctions;

	virtual void sblCElement::HCopie(sblCElement * p);
	
};

#endif