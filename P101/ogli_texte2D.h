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
	class Police_Base : public sblCElement
	{
	public:
		virtual int set(string nvar, lua_State * L)
		{
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

			return sblCElement::set(nvar, L);
		}
		virtual int get(string nvar, lua_State * L)
		{
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

			return sblCElement::set(nvar, L);
		}
		virtual int exec(string nfonc, lua_State * L)
		{
			if (nfonc == "Init")
			{
				Init();
				return 0;
			}

			return sblCElement::exec(nfonc, L);
		}

		virtual sblElement * Copie()
		{
			Police_Base * p = new Police_Base();

			HCopie(p);

			return p;
		}

		string texture, vertexShader, fragmentShader;
		Texture * m_texture;
		Shader * m_shader;

		void Init()
		{
			delete m_texture;
			delete m_shader;
			m_texture = new Texture(texture);
			m_shader = new Shader(vertexShader, fragmentShader);
		}
		Police_Base()
		{

		}
		~Police_Base()
		{
			delete m_texture;
			delete m_shader;
		}

	protected:

		virtual void HCopie(Police_Base * p)
		{
			p->texture = texture;
			p->vertexShader = vertexShader;
			p->fragmentShader = fragmentShader;

			p->Init();

			sblCElement::HCopie(p);
		}

	};

	class Texte2D_Base : public BLutin
	{
	public:
		virtual int set(string nvar, lua_State * L)
		{
			if (nvar == "texte")
			{
				texte = lua_tostring(L, 2);
				return 0;
			}

			return BLutin::set(nvar, L);
		}
		virtual int get(string nvar, lua_State * L)
		{

			return BLutin::set(nvar, L);
		}
		virtual int exec(string nfonc, lua_State * L)
		{

			return BLutin::exec(nfonc, L);
		}

		virtual sblElement * Copie()
		{
			Texte2D_Base * p = new Texte2D_Base();

			HCopie(p);

			return p;
		}

		string texte;
		Police_Base * police;

		void Init()
		{
			glm::vec2 buffer;
			char character;
			float uv_x, uv_y;

			glm::vec2 vertex_up_left, vertex_up_right, vertex_down_right, vertex_down_left;

			delete vertices;
			vertices = new vector < float > ;
			delete tcoord;
			tcoord = new vector < float >;

			for (unsigned int i = 0; i < texte.size; i++){

				glm::vec2 vertex_up_left = glm::vec2(i*size, size);
				glm::vec2 vertex_up_right = glm::vec2(i*size + size, size);
				glm::vec2 vertex_down_right = glm::vec2(i*size + size, 0);
				glm::vec2 vertex_down_left = glm::vec2(i*size, 0);


				vertices->push_back(vertex_up_left.x);
				vertices->push_back(vertex_up_left.y);

				vertices->push_back(vertex_down_left.x);
				vertices->push_back(vertex_down_left.y);

				vertices->push_back(vertex_up_right.x);
				vertices->push_back(vertex_up_right.x);


				vertices->push_back(vertex_down_right.x);
				vertices->push_back(vertex_down_right.y);

				vertices->push_back(vertex_up_right.x);
				vertices->push_back(vertex_up_right.y);

				vertices->push_back(vertex_down_left.x);
				vertices->push_back(vertex_down_left.y);

				character = texte[i];
				uv_x = (character % 16) / 16.0f;
				uv_y = (character / 16) / 16.0f;
			}
		}

		virtual void afficher()
		{
			l_afficher();
		}
		virtual void l_afficher()
		{
			if (visible)
			{
				// Activation du shader

				glUseProgram(police->m_shader->getProgramID());


				// Envoi des vertices

				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, &vertices[0]);
				glEnableVertexAttribArray(0);


				// Envoi des coordonnées de texture

				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, &tcoord[0]);
				glEnableVertexAttribArray(2);

				// Envoi des matrices

				glUniform1f(glGetUniformLocation(police->m_shader->getProgramID(), "profondeur"), z);

				// Verrouillage de la texture

				glBindTexture(GL_TEXTURE_2D, police->m_texture->getID());


				// Rendu

				glDrawArrays(GL_TRIANGLES, 0, vertices.size);


				// Déverrouillage de la texture

				glBindTexture(GL_TEXTURE_2D, 0);


				// Désactivation des tableaux

				glDisableVertexAttribArray(2);
				glDisableVertexAttribArray(0);


				// Désactivation du shader

				glUseProgram(0);

			}
		}

	protected:
		float size;
		vector<float> * tcoord;
		vector<float> * vertices;

		virtual void HCopie(Texte2D_Base * p)
		{
			p->texture = texture;
			p->vertexShader = vertexShader;
			p->fragmentShader = fragmentShader;

			p->Init();

			sblCElement::HCopie(p);
		}
	};
};

#endif