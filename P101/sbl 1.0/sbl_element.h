#include "stdafx.h"

#ifndef SBL_ELEMENT
#define SBL_ELEMENT

using namespace std;

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

#endif