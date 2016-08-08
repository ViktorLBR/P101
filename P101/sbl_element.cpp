#include "stdafx.h"
#include "sbl_element.h"

using namespace std;
using namespace sbl;

int sblCElement::set(string nvar, lua_State * L)
{

	return sblElement::set(nvar, L);
}

int sblCElement::get(string nvar, lua_State * L)
{

	return sblElement::get(nvar, L);
}

int sblCElement::exec(string nfonc, lua_State * L)
{
	if (nfonc == "enregistrerFonc")
	{
		enregFonction(lua_tostring(L, 2), lua_tostring(L, 3), 1);
		return 0;
	}
	if (nfonc == "isfonc")
	{
		sbl::sbl_push(L, isFonction(lua_tostring(L, 2)));
		return 1;
	}

	bool buffer = execFonction(lua_tostring(L,2), lua_tostring(L, 3));
	if (buffer = true)
	{
		return 0;
	}

	return sblElement::exec(nfonc, L);
}

bool sblCElement::isFonction(string nomc)
{
	if (map_fonctions.count(nomc) == 0)
		return false;
	return true;
}

sblElement * sblCElement::Copie()
{
	sblCElement * p = new sblCElement();

	sblCElement::HCopie(p);

	return p;
}

void sblCElement::HCopie(sblCElement * p)
{
	/*lua_Callback * buffer;
	for each (pair<string, sbl::lua_Callback> pr in map_fonctions)
	{
		buffer = new lua_Callback(pr.second);
		p->map_fonctions.emplace(pr.first, buffer);
	}

	sblElement::HCopie(p);*/
}