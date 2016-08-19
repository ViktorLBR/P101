#include "stdafx.h"

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
using namespace glm;

#ifndef OGLI_COORD
#define OGLI_COORD

namespace ogli
{/*
	class Coord2D
	{
	public:
		Coord2D * ancrage;

		Coord2D(float x, float y)
		{
			coord.x = x;
			coord.y = y;
			ancrage = NULL;
		}
		Coord2D()
		{
			Coord2D(0, 0);
		}
		Coord2D(vec2 arg)
		{
			coord = arg;
			ancrage = NULL;
		}
		Coord2D(Coord2D & arg)
		{
			coord = arg.getCoord();
			ancrage = arg.ancrage;
		}

		vec2 getRCoord()
		{
			if (ancrage == NULL)
				return coord;
			else
				return coord + ancrage->getRCoord();
		}
		vec2 getCoord()
		{
			return coord;
		}
		void setCoord(vec2 arg)
		{
			coord = arg;
		}

	protected:
		vec2 coord;
	};*/
};

#endif