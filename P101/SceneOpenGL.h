#include "stdafx.h"
#ifndef DEF_SCENEOPENGL
#define DEF_SCENEOPENGL


// Includes

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


// Autres includes

#include <SDL.h>
#include <iostream>
#include <string>
#include "Shader.h"
#include "Cube.h"
#include "Input.h"
#include "Texture.h"
#include "Caisse.h"
#include "Camera.h"


// Classe

class SceneOpenGL : public sblCElement
{
protected:

	vector<gen::Element3D *> liste_affichage;

public:

    SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre);
    ~SceneOpenGL();

    bool initialiserFenetre();
    bool initGL();
    void bouclePrincipale();

	void pushdisp(gen::Element3D * p)
	{
		liste_affichage.push_back(p);
	}

	bool popdisp(gen::Element3D * p)
	{
		for (vector<gen::Element3D *>::iterator i = liste_affichage.begin(); i < liste_affichage.end(); i++)
		{
			if ((*i) == p)
			{
				liste_affichage.erase(i);
				return true;
			}
		}
		return false;
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
		sblAdr nadr = lua_tonumber(L, 2);
		if (nfonc == "pushdisp")
		{
			liste_affichage.push_back(sbl::convert<gen::Element3D>(hub_lua->getElement(nadr)));
			return 0;
		}
		if (nfonc == "popdisp")
		{
			for (vector<gen::Element3D *>::iterator i = liste_affichage.begin(); i < liste_affichage.end(); i++)
			{
				if ((*i)->getNadr() == nadr)
				{
					liste_affichage.erase(i);
					return 0;
				}
			}
			return 0;
		}

		return sblCElement::exec(nfonc, L);
	}

	virtual sblElement * Copie()
	{
		return NULL;
	}

protected:

    std::string m_titreFenetre;
    int m_largeurFenetre;
    int m_hauteurFenetre;


    SDL_Window* m_fenetre;
    SDL_GLContext m_contexteOpenGL;
    Input m_input;

	virtual void HCopie(SceneOpenGL * p)
	{

		sblCElement::HCopie(p);
	}

};

#endif

