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
public:

    SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre);
    ~SceneOpenGL();

    bool initialiserFenetre();
    bool initGL();

	void get_engine(Input * hinput, ogli::hub_2D * h_2D, gen::hub_3D * h_3D, ogli::hub_Slot * h_slot, ogli::hub_TicInput * h_ticinput)
	{
		//SDL_GL_SetAttribute(SDL_GL_STENCILSIZE, 8);
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


	    // Cam�ra mobile

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
        // Nettoyage de l'�cran
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // Gestion de la cam�ra
        camera->lookAt(modelview);


		// Affichage 3D
		h_3D->actualiser();


		// Affichage 2D
		glClear(GL_DEPTH_BUFFER_BIT);
		h_2D->actualiser();

        // Actualisation de la fen�tre
        SDL_GL_SwapWindow(m_fenetre);
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

