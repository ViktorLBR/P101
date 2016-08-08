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

	virtual int set(string nvar, lua_State * L);
	virtual int get(string nvar, lua_State * L);
	virtual int exec(string nfonc, lua_State * L);
	virtual sblElement * Copie();

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
			return map_fonctions.at(nomc).exec(env->getEnv(), this, args);
		return false;
	}



protected:
	map<string, sbl::lua_Callback> map_fonctions;

	virtual void HCopie(sblCElement * p);
};/*

	void enregFonc(string nomc, string noml)
	{
		if (isFonc(nomc))
			return;
		map_fonc.emplace(nomc, noml);
	}
	bool isFonc(string nom)
	{
		if (map_fonc.count(nom) == 0)
			return false;
		return true;
	}
	template<class ...Arg>bool execFonc(string nomc, lua_State * L, Arg ...args)
	{
		if (!isFonc(nomc))
			return false;
		nom = map_fonc.at(nomc);
		lua_getglobal(L, nom);
		if (!lua_isfunction(L, -1))
		{
			lua_pop(state, 1);
			return false;
		}
		else
		{
			int nbarg = 0;
			sbl::sbl_push(L, nbarg, args);
			lua_call(state, nbarg, 0);
		}

		return true;
	}
	
	bool isVar(string nom)
	{
		if (map_string.count(nom) == 0 && map_float.count(nom) == 0)
			return false;
		return true;
	}
	bool isString(string nom)
	{
		if (map_string.count(nom) == 0)
			return false;
		return true;
	}
	bool isFloat(string nom)
	{
		if (map_float.count(nom) == 0)
			return false;
		return true;
	}
	void ajouterString(string nom, string * val, bool c)
	{
		var_string buffer;
		buffer.c = c;
		buffer.s = val;
		if (isVar(nom) == false && isString(nom) == false)
			map_string.emplace(nom, buffer);
	}
	void ajouterFloat(string nom, float * val, bool c)
	{
		var_float buffer;
		buffer.c = c;
		buffer.f = val;
		if (isVar(nom) == false && isFloat(nom) == false)
			map_float.emplace(nom, buffer);
	}

protected:
	map<string, string> map_fonc;
	struct var_string { string * s; bool c; }; // c indique s'il s'agit d'une variable en c (true) ou en lua (false)
	struct var_float { float * f; bool c; }; // Idem
	map<string, var_string> map_string;
	map<string, var_float> map_float;

	virtual void HCopie(sblCElement * p);
	void Clone(sblCElement * p);
};*/

#endif