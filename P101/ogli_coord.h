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
/*
namespace ogli
{

	class vec2dyn
	{
	public:
		float &a_x, &a_y; // Ancrages
		float x, y;

		float get_x()
		{
			return x + a_x;
		}
		void set_x(float an_x)
		{
			x = an_x - a_x;
		}

		float get_y()
		{
			return y + a_y;
		}
		void set_y(float an_y)
		{
			y = an_y - a_y;
		}

		virtual vec2 get()
		{
			return vec2(get_x(), get_y());
		}
		virtual void set(vec2 v)
		{
			set_x(v.x);
			set_y(v.y);
		}

		virtual vec2 getR()
		{
			return vec2(x, y);
		}
		virtual void setR(vec2 v)
		{
			x = v.x;
			y = v.y;
		}

	protected:

	};

	class vec3dyn
	{
	public:
		float z, &a_z;

		float get_z()
		{
			return z + a_z;
		}
		void set_z(float an_z)
		{
			z = an_z - a_z;
		}


	};
};
*/
#endif