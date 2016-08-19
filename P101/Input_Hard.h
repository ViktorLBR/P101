#include "stdafx.h"

#ifndef INPUT_HARD
#define INPUT_HARD


class lalt_slot : public ogli::b_Slot, public ogli::primitif_TicInput
{
public:
	lalt_slot(Input & i, Camera & c) : input(i), camera(c)
	{
		camera_active = true;
		value = hvalue = i.getTouche(SDL_SCANCODE_LALT);
	}

	virtual void tic(Input & input)
	{
		value = input.getTouche(SDL_SCANCODE_LALT);
	}

	virtual void inChange()
	{
		if (value == false)
		{
			camera_active = !camera_active;
			input.capturerPointeur(camera_active);
			input.afficherPointeur(!camera_active);
		}
		b_Slot::inChange();
	}

	virtual void actualiser()
	{
		b_Slot::actualiser();
		if (camera_active == true)
			camera.deplacer(input);
	}

protected:
	bool camera_active;
	Input & input;
	Camera & camera;
};

#endif