#include "stdafx.h"


#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

#ifndef GEN_3D_ELEMENT
#define GEN_3D_ELEMENT

namespace gen
{
	class Element3DB : public sblCElement
	{
	public:
		virtual void afficher(glm::mat4 &projection, glm::mat4 &modelview)
		{
			execFonction("afficher");
			l_afficher(projection, modelview);
		}

		virtual void l_afficher(glm::mat4 &projection, glm::mat4 &modelview)
		{

		}

		virtual int set(string nvar, lua_State * L)
		{
			return sblCElement::set(nvar, L);
		}

		virtual int get(string nvar, lua_State * L)
		{

			return sblCElement::get(nvar, L);
		}

		virtual int exec(string nfonc, lua_State * L)
		{

			return sblCElement::exec(nfonc, L);
		}

		virtual sblElement * Copie()
		{
			Element3DB * p = new Element3DB();

			HCopie(p);

			return p;
		}

	protected:
		virtual void HCopie(Element3DB * p)
		{
			sblCElement::HCopie(p);
		}
	};

	class Element3D : public Element3DB
	{
	public:
		glm::vec3 coord, orientation;

		Element3D()
		{
			coord = glm::vec3(0, 0, 0);
			orientation = glm::vec3(0, 0, 0);
		}

		virtual int set(string nvar, lua_State * L)
		{
			if (nvar == "coord")
			{
				coord.x = lua_tonumber(L, 2);
				coord.y = lua_tonumber(L, 3);
				coord.z = lua_tonumber(L, 4);
				return 0;
			}
			if (nvar == "orientation")
			{
				orientation.x = lua_tonumber(L, 2);
				orientation.y = lua_tonumber(L, 3);
				orientation.z = lua_tonumber(L, 4);
				return 0;
			}

			return Element3DB::set(nvar, L);
		}

		virtual int get(string nvar, lua_State * L)
		{
			if (nvar == "coord")
			{
				sbl::sbl_push(L, coord.x, coord.y, coord.z);
				return 3;
			}
			if (nvar == "orientation")
			{
				sbl::sbl_push(L, orientation.x, orientation.y, orientation.z);
				return 3;
			}

			return Element3DB::get(nvar, L);
		}

		virtual int exec(string nfonc, lua_State * L)
		{
			return Element3DB::exec(nfonc, L);
		}

		virtual sblElement * Copie()
		{
			Element3D * p = new Element3D();

			HCopie(p);

			return p;
		}

		virtual void afficher(glm::mat4 &projection, glm::mat4 &modelview)
		{
			execFonction("afficher");
			glm::mat4 lmodelview = glm::translate(modelview, coord);
			lmodelview = glm::rotate(lmodelview, orientation.x, glm::vec3(1, 0, 0));
			lmodelview = glm::rotate(lmodelview, orientation.y, glm::vec3(0, 1, 0));
			lmodelview = glm::rotate(lmodelview, orientation.z, glm::vec3(0, 0, 1));
			l_afficher(projection, lmodelview);
		}

	protected:
		virtual void HCopie(Element3D * p)
		{
			p->coord = coord;
			p->orientation = orientation;

			Element3DB::HCopie(p);
		}
	};



	class hub_3D : public gen::Executeur < Element3D >
	{
	public:
		mat4 * projection;
		mat4 * modelview;

		hub_3D()
		{
			nom = "hub_3D";
		}

		virtual void operation(Element3D * p)
		{
			p->afficher(*projection, *modelview);
		}
	};
};

#endif