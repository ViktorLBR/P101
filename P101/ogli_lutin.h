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
	class primitif_Repere2D
	{
	public:
		glm::vec3 * coord;
		glm::vec2 * dim;

		primitif_Repere2D(vec3 * acoord, vec2 * adim)
		{
			coord = acoord;
			dim = adim;
		}
		primitif_Repere2D()
		{
			coord = NULL;
			dim = NULL;
		}
		primitif_Repere2D(primitif_Repere2D * master)
		{
			coord = master->coord;
			dim = master->dim;
		}
	};

	class primitif_Element2D : public primitif_Repere2D
	{
	public:
		string vertexShader, fragmentShader, texture;

		primitif_Element2D(primitif_Repere2D * master) : primitif_Repere2D(master)
		{
			vertexShader = "";
			fragmentShader = "";
			texture = "";
		}

		virtual void afficher()
		{

		}
		virtual void l_afficher()
		{

		}

		virtual void Charger()
		{
			delete m_shader;
			m_shader = new Shader(vertexShader, fragmentShader);
			m_shader->charger();

			delete m_texture;
			m_texture = new Texture(texture);
			m_texture->charger();
		}

	protected:

		virtual void data_evgl()
		{
			// Activation du shader

			glUseProgram(m_shader->getProgramID());


			// Envoi des vertices

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, v_tab);
			glEnableVertexAttribArray(0);


			// Envoi des coordonnées de texture

			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, t_tab);
			glEnableVertexAttribArray(2);


			// Envoi uniforms

			glUniform3f(glGetUniformLocation(m_shader->getProgramID(), "position"), coord->x, coord->y, coord->z);


			// Verrouillage de la texture

			glBindTexture(GL_TEXTURE_2D, m_texture->getID());
		}
		virtual void data_lib()
		{
			// Déverrouillage de la texture

			glBindTexture(GL_TEXTURE_2D, 0);


			// Désactivation des tableaux

			glDisableVertexAttribArray(2);
			glDisableVertexAttribArray(0);


			// Désactivation du shader

			glUseProgram(0);
		}

		float * v_tab;
		float * t_tab;
		Texture * m_texture;
		Shader * m_shader;
	};

	class CoordRectangle2D : public primitif_Repere2D
	{
	public:

		float tab[12];

		CoordRectangle2D(primitif_Repere2D * master) : primitif_Repere2D(master)
		{

		}

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
		primitif_Repere2D * t_Repere2D;
		primitif_Repere2D * v_Repere2D;

		Rectangle(primitif_Repere2D * master) : primitif_Element2D(master)
		{
			coord = master->coord;
			dim = master->dim;

			t_Repere2D = new primitif_Repere2D(new vec3(0, 0, 0), new vec2(1, 0)); 
			v_Repere2D = new primitif_Repere2D(new vec3(0, 0, 0), dim);

			texture_tab = new CoordRectangle2D(t_Repere2D);
			vertex_tab = new CoordRectangle2D(v_Repere2D);

			v_tab = vertex_tab->tab;
			t_tab = texture_tab->tab;
		}

		void Charger()
		{
			primitif_Element2D::Charger();
			vertex_tab->dim = dim;

			vertex_tab->charger();
			texture_tab->charger();

			v_tab = vertex_tab->tab;
			t_tab = texture_tab->tab;
		}

		void afficher()
		{
			l_afficher();
		}
		void l_afficher()
		{
			data_evgl();

			glDrawArrays(GL_TRIANGLES, 0, 6);

			data_lib();
		}

	protected:
		CoordRectangle2D * vertex_tab, * texture_tab;
	};

	class BLutin : public primitif_TicInput, primitif_Repere2D
	{
	public:
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
				coord->z = lua_tonumber(L, 2);
				return 0;
			}
			if (nvar == "dim")
			{
				dim->x = lua_tonumber(L, 2);
				dim->y = lua_tonumber(L, 2);
				return 0;
			}
			if (nvar == "coord")
			{
				coord->x = lua_tonumber(L, 2);
				coord->y = lua_tonumber(L, 3);
				coord->z = lua_tonumber(L, 4);
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
				sbl::sbl_push(L, coord->z);
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
			coord = new vec3(0, 0, 0);
			disp = new Rectangle(this);
			visible = false;
			activate = false;
			in = false;
		}
		BLutin(vec3 * pc, vec2 * pd)
		{
			dim = pd;
			coord = pc;
			disp = new Rectangle(this);
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
			if (input.rectPointeurGL(vec2(coord->x, coord->y), *dim))
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
			in = input.rectPointeurGL(vec2(coord->x, coord->y), *dim);
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