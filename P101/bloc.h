#include "stdafx.h"
#include "Caisse.h"

#ifndef BLOC
#define BLOC

class Bloc : public sblElement
{
public:
	string texture, fragmentShader, vertexShader;
	Bloc() { Obj = NULL; }
	~Bloc() { delete Obj; }

	void afficher(glm::vec3 coord, glm::mat4 &projection, glm::mat4 &modelview)
	{
		glm::mat4 lmodelview = glm::translate(modelview, coord);
		Obj->afficher(projection, lmodelview);
	}

	void charger()
	{
		if (Obj != NULL)
			delete Obj;
		Obj = new Caisse(1.0, vertexShader, fragmentShader, texture);
	}

	virtual int set(string nvar, lua_State * L)
	{
		if (nvar == "texture")
		{
			texture = lua_tostring(L, 2);
			return 0;
		}
		if (nvar == "fragmentShader")
		{
			fragmentShader = lua_tostring(L, 2);
			return 0;
		}
		if (nvar == "vertexShader")
		{
			vertexShader = lua_tostring(L, 2);
			return 0;
		}

		return sblElement::set(nvar, L);
	}

	virtual int get(string nvar, lua_State * L)
	{
		if (nvar == "texture")
		{
			lua_pushstring(L, texture.c_str());
			return 1;
		}
		if (nvar == "fragmentShader")
		{
			lua_pushstring(L, fragmentShader.c_str());
			return 1;
		}
		if (nvar == "vertexShader")
		{
			lua_pushstring(L, vertexShader.c_str());
			return 1;
		}

		return sblElement::get(nvar, L);
	}

	virtual int exec(string nfonc, lua_State * L)
	{
		if (nfonc == "charger")
		{
			charger();
			return 0;
		}

		return sblElement::exec(nfonc, L);
	}

	virtual sblElement * Copie()
	{
		Bloc * p = new Bloc();

		HCopie(p);
		sblElement::HCopie(p);
		p->charger();
		return p;
	}

protected:
	Caisse * Obj;

	virtual void HCopie(Bloc * p)
	{
		p->texture = texture;
		p->fragmentShader = fragmentShader;
		p->vertexShader = vertexShader;
	}
};


#endif
