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
#include "msys.h"


int main(int argc, char **argv)
{
	msys * MainEngine = new msys();

	MainEngine->mainsys();

	// Fin du programme

	return 0;
}
