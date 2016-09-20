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

#include "ogli_lutin.h"

#ifndef OGLI_TEXTE2D
#define OGLI_TEXTE2D

namespace ogli
{
	class Lutin_BTexte : public BLutin
	{
	public:
		string texte;
		float ratio;

		Lutin_BTexte()
		{
			master = NULL;
			dim = new vec2(0, 0);
			coord = new vec3(0, 0, 0);
			visible = false;
			activate = false;
			in = false;
			texte = "";
			fragmentShader = "";
			vertexShader = "";
			texture = "";
			ratio = screen_data->get_ratio();
		}

		virtual int set(string nvar, lua_State * L)
		{
			if (nvar == "texte")
			{
				texte = lua_tostring(L, 2);
				return 0;
			}
			if (nvar == "ratio")
			{
				ratio = lua_tonumber(L, 2);
				return 0;
			}

			return BLutin::set(nvar, L);
		}
		virtual int get(string nvar, lua_State * L)
		{
			if (nvar == "texte")
			{
				sbl_push(L, texte);
				return 1;
			}
			if (nvar == "ratio")
			{
				sbl_push(L, ratio);
				return 1;
			}

			return BLutin::set(nvar, L);
		}
		virtual int exec(string nfonc, lua_State * L)
		{
			if (nfonc == "eqratio")
			{
				ratio = screen_data->get_ratio();
			}

			return BLutin::exec(nfonc, L);
		}


		virtual sblElement * Copie()
		{
			Lutin_BTexte * p = new Lutin_BTexte();

			HCopie(p);

			return p;
		}

		virtual void afficher()
		{
			l_afficher();
		}
		virtual void l_afficher()
		{
			if (texte.length() == 0)
				return;
			if (visible)
			{
				data_evgl();
				glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 2);
				data_lib();
			}
		}

		virtual void charger()
		{
			if (texte.length() == 0)
				return;

			primitif_Element2D::charger();
			glm::vec2 buffer;
			char character;
			float ratio = screen_data->get_ratio();
			float uv_x, uv_y;
			float size = dim->y;
			float sizex = size / ratio;
			dim->x = texte.length() * sizex;

			glm::vec2 vertex_up_left, vertex_up_right, vertex_down_right, vertex_down_left;
			glm::vec2 uv_up_left, uv_up_right, uv_down_right, uv_down_left;

			vertices.clear();
			tcoord.clear();


			for (unsigned int i = 0; i < texte.length(); i++)
			{

				vertex_up_left = vec2(i*sizex, size);
				vertex_up_right = vec2(i*sizex + sizex, size);
				vertex_down_right = vec2(i*sizex + sizex, 0);
				vertex_down_left = vec2(i*sizex, 0);

				push_vec2(vertices, vertex_up_left);
				push_vec2(vertices, vertex_down_left);
				push_vec2(vertices, vertex_up_right);

				push_vec2(vertices, vertex_down_right);
				push_vec2(vertices, vertex_up_right);
				push_vec2(vertices, vertex_down_left);

				character = texte[i];
				uv_x = (character % 16) / 16.0f;
				uv_y = (character / 16) / 16.0f;

				uv_up_left = vec2(uv_x, 1.0f - uv_y);
				uv_up_right = vec2(uv_x + 1.0f / 16.0f, 1.0f - uv_y);
				uv_down_right = vec2(uv_x + 1.0f / 16.0f, 1.0f - (uv_y + 1.0f / 16.0f));
				uv_down_left = vec2(uv_x, 1.0f - (uv_y + 1.0f / 16.0f));

				push_vec2(tcoord, uv_up_left);
				push_vec2(tcoord, uv_down_left);
				push_vec2(tcoord, uv_up_right);
				push_vec2(tcoord, uv_down_right);
				push_vec2(tcoord, uv_up_right);
				push_vec2(tcoord, uv_down_left);
			}
			v_tab = &(vertices)[0];
			t_tab = &(tcoord)[0];
		}

	protected:
		vector<float> tcoord;
		vector<float> vertices;


		void push_vec2(vector<float> & vec, glm::vec2 v2)
		{
			vec.push_back(v2.x);
			vec.push_back(v2.y);
		}

		virtual void HCopie(Lutin_BTexte * p)
		{
			p->texte = texte;

			BLutin::HCopie(p);
		}
	};
};

#endif