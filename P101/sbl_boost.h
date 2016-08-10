#include "stdafx.h"

#include "sbl_main.h"

using namespace std;
using namespace sbl;

#ifndef SBL_BOOST
#define SBL_BOOST

namespace sbl
{
	template<class T>
	void sbl_pushfrag(lua_State * L, T value)
	{
		lua_pushnumber(L, value);
	}

	template < class T>
	void sbl_pushfrag(lua_State * L, const char * value)
	{
		lua_pushstring(L, value);
	}

	template < class T>
	void sbl_pushfrag(lua_State * L, string value)
	{
		lua_pushstring(L, value.c_str());
	}

	template<class T>
	void sbl_push(lua_State * L, T value) {
		sbl_pushfrag<T>(L, value);  // affichage du dernier élément
	}

	template<class T, class ...Args>
	void sbl_push(lua_State * L, T value, Args ... args) {
		sbl_pushfrag<T>(L, value);    // affichage de l'élément courant
		sbl_push(L, args...);            // affichage des autres éléments
	}

	template<class T >
	int sbl_set(T * t, int level, lua_State * L)
	{
		*t = lua_tonumber(L, level)
	}

	template<class T >
	int sbl_set(string * t, int level, lua_State * L)
	{
		*t = lua_tostring(L, level);
	}

	template<class T>
	int sbl_get(T * t, lua_State * L)
	{
		lua_pushnumber(L, *t);
		return 1;
	}

	template<class T>
	int sbl_get(string * t, lua_State * L)
	{
		lua_pushstring(L, t->c_str());
		return 1;
	}

	template<class T>
	void sbl_push(lua_State * L, int  & count, T value)
	{
		count++;
		sbl_pushfrag<T>(L, value);
	}

	template<class T, class ...Args>
	void sbl_push(lua_State * L, int  & count, T value, Args ...args)
	{
		count++;
		sbl_pushfrag<T>(L, value);
		sbl_push(L, count, args...);
	}

	template<class T, class U>
	T * convert(U * p)
	{
		return reinterpret_cast<T *>(p);
	}

	class lua_Callback
	{
	public:
		lua_Callback(string nom, int nbarg)
		{
			this->nbarg = nbarg;
			this->nomlua = nom;
		}
		lua_Callback(lua_Callback & ref)
		{
			nbarg = ref.nbarg;
			nomlua = ref.nomlua;
		}
		template<class Args> bool exec(lua_State * L, sblElement * p, Args args)
		{
			pElement pext = hub_lua->getcible();
			sblAdr ndrbuffer = NULL;
			if (pext != NULL)
				ndrbuffer = pext->getNadr();

			lua_getglobal(L, nomlua.c_str());
			if (!lua_isfunction(L, -1))
			{
				lua_pop(L, 1);
				return false;
			}


			sbl::sbl_push(L, args);
			hub_lua->charger(p->getNadr());

			lua_call(L, nbarg, 0);

			if (ndrbuffer != NULL)
				hub_lua->charger(ndrbuffer);
			else
				hub_lua->fermer();
			return true;
		}

	protected:
		int nbarg;
		string nomlua;
	};
};


#endif