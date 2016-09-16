#include "stdafx.h"
#include "SceneOpenGL.h"


// Permet d'éviter la ré-écriture du namespace glm::

using namespace glm;



// Constructeur de Destucteur

SceneOpenGL::SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre) : m_titreFenetre(titreFenetre), m_largeurFenetre(largeurFenetre),
                                                                                             m_hauteurFenetre(hauteurFenetre), m_fenetre(0), m_contexteOpenGL(0),
                                                                                             m_input()
{
	nom = "SceneOpenGL";
}


SceneOpenGL::~SceneOpenGL()
{
    SDL_GL_DeleteContext(m_contexteOpenGL);
    SDL_DestroyWindow(m_fenetre);
    SDL_Quit();
}


// Méthodes

bool SceneOpenGL::initialiserFenetre()
{
    // Initialisation de la SDL

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return false;
    }


    // Version d'OpenGL

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);


    // Double Buffer

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


    // Création de la fenêtre

    m_fenetre = SDL_CreateWindow(m_titreFenetre.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_largeurFenetre, m_hauteurFenetre, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(m_fenetre == 0)
    {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return false;
    }


    // Création du contexte OpenGL

    m_contexteOpenGL = SDL_GL_CreateContext(m_fenetre);

    if(m_contexteOpenGL == 0)
    {
        std::cout << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_fenetre);
        SDL_Quit();

        return false;
    }

    return true;
}

bool SceneOpenGL::initGL()
{
    #ifdef WIN32

        // On initialise GLEW

        GLenum initialisationGLEW( glewInit() );


        // Si l'initialisation a échoué :

        if(initialisationGLEW != GLEW_OK)
        {
            // On affiche l'erreur grâce à la fonction : glewGetErrorString(GLenum code)

            std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGLEW) << std::endl;


            // On quitte la SDL

            SDL_GL_DeleteContext(m_contexteOpenGL);
            SDL_DestroyWindow(m_fenetre);
            SDL_Quit();

            return false;
        }

    #endif


    // Activation du Depth Buffer

    glEnable(GL_DEPTH_TEST);


    // Tout s'est bien passé, on retourne true

    return true;
}

void SceneOpenGL::bouclePrincipale()
{
    // Variables

    Uint32 frameRate (1000 / 30);
    Uint32 debutBoucle(0), finBoucle(0), tempsEcoule(0);


    // Matrices

    mat4 projection;
    mat4 modelview;

    projection = perspective(70.0, (double) m_largeurFenetre / m_hauteurFenetre, 0.1, 100.0);
    modelview = mat4(1.0);

	// hub
	ogli::hub_Slot * h_slot = new ogli::hub_Slot();
	ogli::hub_TicInput * h_ticinput = new ogli::hub_TicInput(m_input);
	ogli::hub_2D * h_2D = new ogli::hub_2D();


	// Map

	EnvLua * env = new EnvLua();
	L_gen = env->getEnv();


	P101_Cubix::BlocMap * p_map = new P101_Cubix::BlocMap();

	Bloc * p_bloc_test = new Bloc();
	p_bloc_test->nom = "bloc";
	p_bloc_test->texture = "DATA/Textures/alpha.png";
	p_bloc_test->fragmentShader = "DATA/Shaders/texture.frag";
	p_bloc_test->vertexShader = "DATA/Shaders/texture.vert";

	ogli::BLutin * blutin = new ogli::BLutin();
	blutin->texture = "DATA/Textures/alpha.png";
	blutin->vertexShader = "DATA/Shaders/texture2Dp.vert";
	blutin->fragmentShader = "DATA/Shaders/texture2Dp.frag";

	hub_lua = new sblHub();

	hub_lua->ajouter_element(this);
	hub_lua->lib_ajouter("blutin", blutin);
	hub_lua->lib_ajouter("bloc", p_bloc_test);
	hub_lua->lib_ajouter("map", p_map);


	// Ajout des hubs à sbl_hub
	hub_lua->ajouter_element(h_slot);
	hub_lua->ajouter_element(h_ticinput);
	hub_lua->ajouter_element(h_2D);


    // Caméra mobile

    Camera camera(vec3(3, 3, 3), vec3(0, 0, 0), vec3(0, 1, 0), 1, 0.5);
    m_input.afficherPointeur(false);
    m_input.capturerPointeur(true);

	// Inputs
	lalt_slot lalt_s(m_input, camera);
	h_slot->push("lalt_camera", &lalt_s);
	h_ticinput->push("lalt_camera", &lalt_s);

	// LUA
	env->Exec("config.lua");


	blutin = convert<ogli::BLutin>(hub_lua->getnom("testblutin"));

    // Boucle principale

    while(!m_input.terminer())
    {
        // On définit le temps de début de boucle
        debutBoucle = SDL_GetTicks();


        // Gestion des évènements
        m_input.updateEvenements();
        if(m_input.getTouche(SDL_SCANCODE_ESCAPE))
           break;
		h_ticinput->actualiser();
		h_slot->actualiser();


        // Nettoyage de l'écran
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // Gestion de la caméra
        camera.lookAt(modelview);


		// Affichage 3D
		for each(gen::Element3D * p in liste_affichage)
		{
			p->afficher(projection, modelview);
		}


		// Affichage 2D
		glClear(GL_DEPTH_BUFFER_BIT);
		h_2D->actualiser();

        // Actualisation de la fenêtre
        SDL_GL_SwapWindow(m_fenetre);


        // Calcul du temps écoulé
        finBoucle = SDL_GetTicks();
        tempsEcoule = finBoucle - debutBoucle;


        // Si nécessaire, on met en pause le programme
        if(tempsEcoule < frameRate)
            SDL_Delay(frameRate - tempsEcoule);
    }
}

