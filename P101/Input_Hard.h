#include "stdafx.h"

#ifndef INPUT_HARD
#define INPUT_HARD

using namespace ogli;

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

class cmd_slot : public ogli::b_Slot, public ogli::primitif_TicInput
{
public:
	cmd_slot(hub_2D & h_2D, Input & input) : input(input)
	{
		cmd_active = false;
		value = hvalue = input.getTouche(SDL_SCANCODE_GRAVE);


		lutin_boite = new BLutin();
		lutin_texte = new Lutin_BTexte();

		lutin_boite->vertexShader = lutin_texte->vertexShader = "DATA/Shaders/texture2Dp.vert";
		lutin_boite->fragmentShader = lutin_texte->fragmentShader = "DATA/Shaders/texture2Dp.frag";
		lutin_texte->texture = "DATA/Textures/font2.png";
		lutin_boite->texture = "DATA/Textures/alpha.png";

		*(lutin_boite->t_Repere2D->dim) /= 2;
		(lutin_boite->t_Repere2D->coord)->x += 0.5;

		lutin_texte->dim = new glm::vec2(0, 0.05);
		lutin_boite->dim = new glm::vec2(2, 0.05);

		lutin_boite->coord = new glm::vec3(-1, -1, 0.01);
		lutin_texte->coord = new glm::vec3(0, 0, -0.005);

		lutin_texte->link(lutin_boite);

		lutin_boite->charger();
		lutin_texte->charger();

		h_2D.push("cmd_boite", lutin_boite);
		h_2D.push("cmd_texte", lutin_texte);

		stream = new sstream_c();
	}

	virtual void tic(Input & input)
	{
		value = input.getTouche(SDL_SCANCODE_GRAVE);
	}

	virtual void actualiser_visible()
	{
		lutin_boite->visible = cmd_active;
		lutin_texte->visible = cmd_active;
	}

	virtual void inChange()
	{
		if (value == false)
		{
			cmd_active = !cmd_active;
			actualiser_visible();
			stream->onBackspaceKey();
			if (cmd_active == true)
			{
				h_sstream->push("cmd_stream", stream);
			}
			else
			{
				h_sstream->pop("cmd_stream");
			}
		}
		b_Slot::inChange();
	}

	virtual void actualiser()
	{
		b_Slot::actualiser();
		if (cmd_active == true)
		{
			cmd = stream->input;
			if (stream->get_fin() == true)
			{
				delete stream;
				stream = new sstream_c();
				env->ExecS(cmd);
				cmd = "";
			}
			if (lutin_texte->texte != cmd)
			{
				lutin_texte->texte = cmd;
				lutin_texte->charger();
			}
		}
	}

protected:
	bool cmd_active;
	sstream_c * stream;
	string cmd;
	ogli::BLutin * lutin_boite;
	ogli::Lutin_BTexte * lutin_texte;
	Input & input;
};

#endif