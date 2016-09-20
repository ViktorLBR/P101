#include "stdafx.h"

#include <SDL.h>

#ifndef GEN_PHYDATA
#define GEN_PHYDATA

class gen_PhyData
{
protected:
	Uint32 debut, fin;

public:
	Uint32 Delta_t;

	void init()
	{
		debut = 0;
	}

	void actualiser()
	{
		fin = SDL_GetTicks();
		Delta_t = fin - debut;
		debut = fin;
	}
};

class gen_ScreenData
{
public:

	float get_ratio()
	{
		float ratio = ((float)*y_window) / ((float)*x_window);
		return ratio;
	}

	int * x_window, * y_window;
};

extern gen_PhyData * dt_mainsys;
extern gen_ScreenData * screen_data;

#endif