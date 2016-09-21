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

	primitif_Repere2D * primitif_RepereGLCentral = new primitif_Repere2D(new vec3(0, 0, 0), new vec2(0, 0));

	class primitif_Element2D : public primitif_Repere2D
	{
	public:
		string vertexShader, fragmentShader, texture;
		primitif_Repere2D * repere;

		primitif_Element2D(primitif_Repere2D * master)
		{
			repere = master;
			vertexShader = "";
			fragmentShader = "";
			texture = "";
		}
		primitif_Element2D() : primitif_Repere2D()
		{
			repere = NULL;
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

		virtual void charger()
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
			vec3 bcoord(*coord);
			if (repere != NULL)
				bcoord += *(repere->coord);
			glUniform3f(glGetUniformLocation(m_shader->getProgramID(), "position"), bcoord.x, bcoord.y, bcoord.z);


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

		virtual void charger()
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
	/*class Calque : public primitif_Element2D
	{
	public:
		primitif_Repere2D * t_Repere2D;
		primitif_Repere2D * v_Repere2D;

		virtual void charger()
		{
			primitif_Element2D::charger();
			vertex_tab->dim = dim;

			vertex_tab->charger();
			texture_tab->charger();

			v_tab = vertex_tab->tab;
			t_tab = texture_tab->tab;
		}

		Calque()
		{
			t_Repere2D = new primitif_Repere2D(new vec3(0, 0, 0), new vec2(1, 1));
			v_Repere2D = new primitif_Repere2D(new vec3(0, 0, 0), dim);

			texture_tab = new CoordRectangle2D(t_Repere2D);
			vertex_tab = new CoordRectangle2D(v_Repere2D);

			texture = "DATA/Textures/alpha.png";
			vertexShader = "DATA/Shaders/texture2Dp.vert";
			fragmentShader = "DATA/Shaders/texture2Dp.frag";

			v_tab = vertex_tab->tab;
			t_tab = texture_tab->tab;
		}

		void afficher()
		{
			l_afficher();
		}
		void l_afficher()
		{
			glEnable(GL_STENCIL_TEST);

			// Paramètres stencil
			glStencilFunc(GL_ALWAYS, 1, 0xFF); // Set any stencil to 1
			glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
			glStencilMask(0xFF); // Write to stencil buffer
			glDepthMask(GL_FALSE); // Don't write to depth buffer

			glDrawArrays(GL_TRIANGLES, 0, 6);

			// Paramètres de base
			glStencilFunc(GL_EQUAL, 1, 0xFF); // Pass test if stencil value is 1
			glStencilMask(0x00); // Don't write anything to stencil buffer
			glDepthMask(GL_TRUE); // Write to depth buffer

			glDisable(GL_STENCIL_TEST);
		}

	protected:
		CoordRectangle2D * vertex_tab, *texture_tab;
	};*/

	class BLutin : public primitif_TicInput, public primitif_Element2D
	{
	public:
		bool in; // Vrai si le pointeur est sur le bouton
		bool activate; // Vrai si le pointeur est activé
		bool action_actif;
		bool visible;
		bool calque;

		primitif_Repere2D * t_Repere2D;
		primitif_Repere2D * v_Repere2D;

		BLutin * master;

		virtual int set(string nvar, lua_State * L)
		{
			if (nvar == "action_actif")
			{
				action_actif = lua_toboolean(L, 2);
				return 0;
			}
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
			if (nvar == "action_actif")
			{
				sbl::sbl_push(L, action_actif);
				return 1;
			}
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
			if (nfonc == "link")
			{
				sblAdr nadr = lua_tonumber(L, 2);
				if (nadr == 0)
					unlink();
				else
					link(convert<ogli::BLutin>(hub_lua->getElement(nadr)));
				return 0;
			}

			return sblCElement::exec(nfonc, L);
		}

		virtual void link(BLutin * master)
		{
			this->master = master;
			this->repere = master;
		}
		virtual void unlink()
		{
			master = NULL;
			repere = NULL;
		}

		virtual void charger()
		{
			primitif_Element2D::charger();
			vertex_tab->dim = dim;

			vertex_tab->charger();
			texture_tab->charger();

			v_tab = vertex_tab->tab;
			t_tab = texture_tab->tab;
		}

		BLutin()
		{
			master = NULL;

			t_Repere2D = new primitif_Repere2D(new vec3(0, 0, 0), new vec2(1, 1));
			v_Repere2D = new primitif_Repere2D(new vec3(0, 0, 0), dim);

			texture_tab = new CoordRectangle2D(t_Repere2D);
			vertex_tab = new CoordRectangle2D(v_Repere2D);

			v_tab = vertex_tab->tab;
			t_tab = texture_tab->tab;

			dim = new vec2(0, 0);
			coord = new vec3(0, 0, 0);
			visible = false;
			activate = false;
			action_actif = true;
			calque = true;
			in = false;
		}

		virtual void afficher()
		{
			l_afficher();
		}
		virtual void l_afficher()
		{
			if (visible)
			{
				if (calque == true)
					;

				data_evgl();
				glDrawArrays(GL_TRIANGLES, 0, 6);
				data_lib();
			}
		}

		virtual void tic(Input &input)
		{
			if (!action_actif)
				return;
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
		CoordRectangle2D * vertex_tab, *texture_tab;

		virtual void HCopie(BLutin * p)
		{
			p->texture = texture;
			p->vertexShader = vertexShader;
			p->fragmentShader = fragmentShader;

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

	class RLutin : public BLutin, public hub_2D
	{
	public:
		
	};
};

#endif