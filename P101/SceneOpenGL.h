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
#include "Texture.h"
#include "Caisse.h"
#include "Camera.h"
#include "Input.h"


// Classe

class SceneOpenGL : public sblCElement
{
protected:

	vector<gen::Element3D *> liste_affichage;
	map<string, ogli::BLutin *> liste_2D;

public:

    SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre);
    ~SceneOpenGL();

    bool initialiserFenetre();
    bool initGL();

	void get_engine(Input * hinput, ogli::hub_2D * h_2D, gen::hub_3D * h_3D, ogli::hub_Slot * h_slot, ogli::hub_TicInput * h_ticinput)
	{
		this->input = hinput;
		this->h_2D = h_2D;
		this->h_3D = h_3D;
		this->h_slot = h_slot;
		this->h_ticinput = h_ticinput;
	}
	void init_engine()
	{
		// Variables

	    frameRate = 1000 / 30;
		debutBoucle = finBoucle = tempsEcoule = 0;

		screen_data->x_window = &m_hauteurFenetre;
		screen_data->y_window = &m_largeurFenetre;


	    // Matrices

	    projection = perspective(70.0, (double) m_largeurFenetre / m_hauteurFenetre, 0.1, 100.0);
	    modelview = mat4(1.0);
		h_3D->modelview = &modelview;
		h_3D->projection = &projection;


	    // Caméra mobile

	    camera = new Camera(vec3(3, 3, 3), vec3(0, 0, 0), vec3(0, 1, 0), 1, 0.5);
	    input->afficherPointeur(false);
	    input->capturerPointeur(true);
		input->x_window = m_hauteurFenetre;
		input->y_window = m_largeurFenetre;


		// Inputs

		lalt_s = new lalt_slot(*input, *camera);
		h_slot->push("lalt_camera", lalt_s);
		h_ticinput->push("lalt_camera", lalt_s);
	}
	void tic()
	{
        // Nettoyage de l'écran
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // Gestion de la caméra
        camera->lookAt(modelview);


		// Affichage 3D
		h_3D->actualiser();


		// Affichage 2D
		glClear(GL_DEPTH_BUFFER_BIT);
		h_2D->actualiser();

        // Actualisation de la fenêtre
        SDL_GL_SwapWindow(m_fenetre);
	}

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

	bool push2D(string nom, ogli::BLutin * p)
	{
		if (liste_2D.count(nom) != 0) return false;
		liste_2D.emplace(nom, p);
	}

	bool pop2D(string nom)
	{
		if (liste_2D.count(nom) == 0) return false;
		liste_2D.erase(nom);
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
		if (nfonc == "push2D")
		{
			push2D(lua_tostring(L, 2), sbl::convert<ogli::BLutin>(hub_lua->getnadr(lua_tonumber(L, 3))));
			return 0;
		}
		if (nfonc == "pop2D")
		{
			pop2D(lua_tostring(L, 2));
			return 0;
		}

		return sblCElement::exec(nfonc, L);
	}

	virtual sblElement * Copie()
	{
		return NULL;
	}

protected:
	Uint32 frameRate, debutBoucle, finBoucle, tempsEcoule;

	mat4 projection, modelview;

	Camera * camera;

    std::string m_titreFenetre;
    int m_largeurFenetre;
    int m_hauteurFenetre;

	ogli::hub_Slot * h_slot;
	ogli::hub_TicInput * h_ticinput;
	ogli::hub_2D * h_2D;
	gen::hub_3D * h_3D;
	Input * input;

	lalt_slot * lalt_s;

    SDL_Window* m_fenetre;
    SDL_GLContext m_contexteOpenGL;

	virtual void HCopie(SceneOpenGL * p)
	{

		sblCElement::HCopie(p);
	}

};

#endif

