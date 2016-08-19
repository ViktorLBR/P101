#include "stdafx.h"
#ifndef DEF_INPUT
#define DEF_INPUT

// Include

#include <SDL.h>

// Includes GLM

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

// Classe

class Input
{
    public:

    Input();
    ~Input();

    void updateEvenements();
    bool terminer() const;
    void afficherPointeur(bool reponse) const;
    void capturerPointeur(bool reponse);
	bool pointeurCapture;

    bool getTouche(const SDL_Scancode touche) const;
    bool getBoutonSouris(const Uint8 bouton) const;
    bool mouvementSouris() const;

    int getX() const;
    int getY() const;

    int getXRel() const;
	int getYRel() const;

	bool entre(float a, float b, float ref)
	{
		if (a > b)
		{
			if (ref <= a && ref >= b)
				return true;
			return false;
		}
		if (ref <= b && ref >= a)
			return true;
		return false;
	}
	bool entre(vec2 vec, float ref)
	{
		return entre(vec.x, vec.y, ref);
	}

	vec2 gl_to_sdl(vec2 input)
	{
		return vec2((input.x + 1) * 1280 / 2, (1 - input.y) * 720 / 2);
	}
	vec2 gl_to_sdlN(vec2 input)
	{
		return vec2(input.x * 1280 / 2, input.y * -720 / 2);
	}

	bool rectHB_c(vec2 A, vec2 B, vec2 HB)
	{
		if (entre(A.x, B.x, HB.x))
			if (entre(A.y, B.y, HB.y))
				return true;
		return false;
	}
	bool rectHB_d(vec2 A, vec2 B, vec2 HB)
	{
		return rectHB_c(A, A + B, HB);
	}
	bool rectHB_GL_d(vec2 A, vec2 B, vec2 HB)
	{
		return rectHB_d(gl_to_sdl(A), gl_to_sdlN(B), HB);
	}

	bool rectPointeurGL(vec2 A, vec2 B)
	{
		return rectHB_GL_d(A, B, vec2(m_x, m_y));
	}
	bool rectPointeur(vec2 A, vec2 B)
	{
		return rectHB_d(A, B, vec2(m_x, m_y));
	}

    private:

    SDL_Event m_evenements;
    bool m_touches[SDL_NUM_SCANCODES];
    bool m_boutonsSouris[8];

    int m_x;
    int m_y;
    int m_xRel;
    int m_yRel;

    bool m_terminer;
};


#endif

