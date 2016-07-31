// Projet 101 moteur.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define GLEW_STATIC
#pragma comment(lib, "opengl32.lib")
#ifdef WIN32
#include <GL/glew.h>

#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

#endif

#include <SDL.h>
#include <iostream>
#include "SceneOpenGL.h"


int main(int argc, char **argv)
{
	// Création de la sène

	SceneOpenGL scene("OpenGL", 1280, 720);

	EnvLua * env = new EnvLua();


	// Initialisation de la scène

	if (scene.initialiserFenetre() == false)
		return -1;

	if (scene.initGL() == false)
		return -1;


	// Boucle Principale

	scene.bouclePrincipale();


	// Fin du programme

	return 0;
}
