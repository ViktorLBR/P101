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
using namespace std;

// Classe

class sstream_c
{
protected:
	bool fin;

public:
	string input;

	bool get_fin()
	{
		return fin;
	}

	sstream_c()
	{
		input = "";
		fin = false;
	}

	virtual void onString(string s)
	{
		if (fin)
			return;
		input += s;
	}

	virtual void onBackspaceKey()
	{
		if (fin)
			return;
		if (input.length() > 0)
			input = input.substr(0, input.length() - 1);
	}

	virtual void onEnterKey()
	{
		if (fin)
			return;
		fin = true;
	}
};

class hub_sstream : public gen::Executeur < sstream_c >
{
public:
	enum ev { onString, onBackspaceKey, onEnterKey} sstream_event;
	bool auto_ex;
	string s;

	void set(string ns)
	{
		s = ns;
		sstream_event = onString;
		if (auto_ex)
			this->actualiser();
	}
	void set(ev nev)
	{
		s = "";
		sstream_event = nev;
		if (auto_ex)
			this->actualiser();
	}

	hub_sstream()
	{
		nom = "hub_sstream";
		auto_ex = true;
	}

	virtual void operation(sstream_c * p)
	{
		if (sstream_event == onString)
			p->onString(s);
		else
			if (sstream_event == onBackspaceKey)
				p->onBackspaceKey();
			else
				if (sstream_event == onEnterKey)
					p->onEnterKey();
	}
};

extern hub_sstream * h_sstream;

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
		return vec2((input.x + 1) * y_window / 2, (1 - input.y) * x_window / 2);
	}
	vec2 gl_to_sdlN(vec2 input)
	{
		return vec2(input.x * y_window / 2, input.y * -x_window / 2);
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


	int x_window, y_window;

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

