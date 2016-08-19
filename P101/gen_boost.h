#include "stdafx.h"


#ifndef GEN_BOOST
#define GEN_BOOST

using namespace std;

namespace gen
{
	template<class T>class Executeur : public sblElement
	{
	public:
		virtual int exec(string nfonc, lua_State * L)
		{
			if (nfonc == "push")
			{
				sbl::sbl_push(L, push(lua_tostring(L, 2), convert<T>(hub_lua->getElement(lua_tonumber(L, 3)))));
				return 1;
			}
			if (nfonc == "pop")
			{
				sbl::sbl_push(L, pop(lua_tostring(L, 2)));
				return 1;
			}

			return sblElement::exec(nfonc, L);
		}

		bool is(string nom)
		{
			if (liste_exec.count(nom) == 0)
				return false;
			return true;
		}
		bool push(string nom, T * p)
		{
			if (!is(nom))
			{
				liste_exec.emplace(nom, p);
				return true;
			}
			return false;
		}
		bool pop(string nom)
		{
			if (is(nom))
			{
				liste_exec.erase(nom);
				return true;
			}
			return false;
		}

		virtual void operation(T * p)
		{

		}
		virtual void actualiser()
		{
			for each(pair<string, T *> p in liste_exec)
				operation(p.second);
		}

	protected:
		map<string, T *> liste_exec;
	};
}

#endif
