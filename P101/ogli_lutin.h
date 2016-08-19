#include "stdafx.h"
#include "Texture.h"
#include "Shader.h"
#include "Input.h"

// Includes OpenGL

#ifdef WIN32
#include <GL/glew.h>

#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

#endif


// Includes GLM

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace sbl;

#ifndef OGLI_LUTIN
#define OGLI_LUTIN

using namespace glm;

namespace ogli
{
	class primitif_Element2D
	{
	public:
		virtual void afficher()
		{

		}
		virtual void l_afficher()
		{

		}
	};

	class CoordRectangle2D
	{
	public:
		glm::vec2 * coord;
		glm::vec2 * dim;

		float tab[12];

		void charger()
		{
			float buffer[] =
			{

				coord->x, coord->y,
				coord->x + dim->x, coord->y,
				coord->x + dim->x, coord->y + dim->y,

				coord->x, coord->y,
				coord->x, coord->y + dim->y,
				coord->x + dim->x, coord->y + dim->y,
			};
			for (int i = 0; i < 12; i++)
			{
				tab[i] = buffer[i];
			}
		}

	protected:
	};

	class Rectangle : public primitif_Element2D
	{
	public:
		glm::vec2 * coord;
		float * z;
		glm::vec2 * dim;
		glm::vec2 * t_coord, * t_dim;
		string vertexShader, fragmentShader, texture;

		Rectangle(vec2 * acoord, vec2 * adim, float * pz)
		{
			coord = acoord;
			dim = adim;
			z = pz;
			texture_tab.coord = t_coord = new vec2(0, 0);
			texture_tab.dim = t_dim = new vec2(1, 1);
			vertex_tab.coord = coord;
			vertex_tab.dim = dim;
		}

		void Charger()
		{
			vertex_tab.coord = coord;
			vertex_tab.dim = dim;
			delete m_shader;
			m_shader = new Shader(vertexShader, fragmentShader);
			m_shader->charger();
			delete m_texture;
			m_texture = new Texture(texture);
			m_texture->charger();
			vertex_tab.charger();
			texture_tab.charger();
		}

		void afficher()
		{
			l_afficher();
		}
		void l_afficher()
		{
			// Activation du shader

			glUseProgram(m_shader->getProgramID());


			// Envoi des vertices

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertex_tab.tab);
			glEnableVertexAttribArray(0);


			// Envoi des coordonnées de texture

			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, texture_tab.tab);
			glEnableVertexAttribArray(2);

			// Envoi des matrices

			glUniform1f(glGetUniformLocation(m_shader->getProgramID(), "profondeur"), *z);

			// Verrouillage de la texture

			glBindTexture(GL_TEXTURE_2D, m_texture->getID());


			// Rendu

			glDrawArrays(GL_TRIANGLES, 0, 6);


			// Déverrouillage de la texture

			glBindTexture(GL_TEXTURE_2D, 0);


			// Désactivation des tableaux

			glDisableVertexAttribArray(2);
			glDisableVertexAttribArray(0);


			// Désactivation du shader

			glUseProgram(0);
		}

	protected:
		Texture * m_texture;
		Shader * m_shader;
		CoordRectangle2D vertex_tab, texture_tab;
	};

	class BLutin : public primitif_TicInput
	{
	public:
		glm::vec2 * coord;
		glm::vec2 * dim;
		float z;

		bool in; // Vrai si le pointeur est sur le bouton
		bool activate; // Vrai si le pointeur est activé
		bool visible;

		string texture, vertexShader, fragmentShader;

		virtual int set(string nvar, lua_State * L)
		{
			if (nvar == "visible")
			{
				visible = lua_toboolean(L, 2);
				return 0;
			}
			if (nvar == "texture")
			{
				texture = lua_tostring(L, 2);
				return 0;
			}
			if (nvar == "vertexShader")
			{
				vertexShader = lua_tostring(L, 2);
				return 0;
			}
			if (nvar == "fragmentShader")
			{
				fragmentShader = lua_tostring(L, 2);
				return 0;
			}
			if (nvar == "profondeur")
			{
				z = lua_tonumber(L, 2);
				return 0;
			}
			if (nvar == "dim")
			{
				delete dim;
				dim = new vec2(lua_tonumber(L, 2), lua_tonumber(L, 3));
				return 0;
			}
			if (nvar == "coord")
			{
				delete coord;
				coord = new vec2(lua_tonumber(L, 2), lua_tonumber(L, 3));
				return 0;
			}

			return sblCElement::set(nvar, L);
		}
		virtual int get(string nvar, lua_State * L)
		{
			if (nvar == "visible")
			{
				sbl::sbl_push(L, visible);
				return 1;
			}
			if (nvar == "texture")
			{
				sbl::sbl_push(L, texture);
				return 1;
			}
			if (nvar == "vertexShader")
			{
				sbl::sbl_push(L, vertexShader);
				return 1;
			}
			if (nvar == "fragmentShader")
			{
				sbl::sbl_push(L, fragmentShader);
				return 1;
			}
			if (nvar == "profondeur")
			{
				sbl::sbl_push(L, z);
				return 1;
			}
			if (nvar == "dim")
			{
				sbl::sbl_push(L, dim->x, dim->y);
				return 2;
			}
			if (nvar == "coord")
			{
				sbl::sbl_push(L, coord->x, coord->y);
				return 2;
			}

			if (nvar == "in")
			{
				sbl::sbl_push(L, in);
				return 1;
			}
			if (nvar == "activate")
			{
				sbl::sbl_push(L, activate);
				return 1;
			}

			return sblCElement::get(nvar, L);
		}
		virtual int exec(string nfonc, lua_State * L)
		{
			if (nfonc == "charger")
			{
				charger();
				return 0;
			}

			return sblCElement::exec(nfonc, L);
		}

		void charger()
		{
			disp->texture = texture;
			disp->vertexShader = vertexShader;
			disp->fragmentShader = fragmentShader;
			disp->Charger();
		}

		BLutin()
		{
			dim = new vec2(0, 0);
			coord = new vec2(0, 0);
			z = 0.1;
			disp = new Rectangle(coord, dim, &z);
			visible = false;
			activate = false;
			in = false;
		}
		BLutin(vec2 * pc, vec2 * pd)
		{
			dim = pd;
			coord = pc;
			z = 0.1;
			disp = new Rectangle(coord, dim, &z);
			visible = false;
			activate = false;
			in = false;
		}

		virtual void afficher()
		{
			l_afficher();
		}
		virtual void l_afficher()
		{
			if (visible)
				disp->afficher();
		}

		virtual void tic(Input &input)
		{
			if (input.rectPointeurGL(*coord, *dim))
			{
				if (in == false)
					onEnter();
				else
					onAbove();
				if (activate == true && input.getBoutonSouris(1) == false) // Clic
					onClic();
				else
					if (activate == true && input.getBoutonSouris(1) == true)
						onActivate();
			}
			else
				if (in == true)
					onLeaving();
			in = input.rectPointeurGL(*coord, *dim);
			activate = input.getBoutonSouris(1);
			normal();
		}
		virtual void normal()
		{
			execFonction("normal", 0);
		}

		virtual void onClic()
		{
			execFonction("onClic", 0);
		}
		virtual void onActivate()
		{
			execFonction("onActivate", 0);
		}
		virtual void onEnter()
		{
			execFonction("onEnter", 0);
		}
		virtual void onLeaving()
		{
			execFonction("onLeaving", 0);
		}
		virtual void onAbove()
		{
			execFonction("onAbove", 0);
		}

		sblElement * Copie()
		{
			BLutin * p = new BLutin();

			BLutin::HCopie(p);

			return p;
		}

	protected:
		Rectangle * disp;

		virtual void HCopie(BLutin * p)
		{
			p->texture = texture;
			p->vertexShader = vertexShader;
			p->fragmentShader = fragmentShader;
			p->z = z;
			delete p->dim;
			delete p->coord;
			p->dim = dim;
			p->disp->dim = dim;
			p->disp->coord = coord;
			p->coord = coord;

			sblCElement::HCopie(p);
		}
	};

	class hub_2D : public gen::Executeur < BLutin >
	{
	public:
		hub_2D()
		{
			nom = "hub_2D";
		}

		virtual void operation(BLutin * p)
		{
			p->afficher();
		}
	};
};

#endif