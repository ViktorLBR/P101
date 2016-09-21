#include "stdafx.h"

#ifndef P101_MSYS
#define P101_MSYS

class msys
{
public:

	msys() : input(), h_slot(), h_ticinput(input), h_2D(), h_3D()
	{
		scene_opengl = new SceneOpenGL("P101", 1600, 900);
		if (scene_opengl->initialiserFenetre() == false)
			throw "erreur init";
		if (scene_opengl->initGL() == false)
			throw "erreur init";
		screen_data = new gen_ScreenData();
		scene_opengl->get_engine(&input, &h_2D, &h_3D, &h_slot, &h_ticinput);
		scene_opengl->init_engine();

		env = new EnvLua();
		L_gen = env->getEnv();

		Init();
	}

	void Init()
	{
		dt_mainsys = new gen_PhyData();
		dt_mainsys->init();
		target = 1000 / 60;

		hub_lua = new sblHub();

		// Ajout des hubs à sbl_hub
		hub_lua->ajouter_element(&h_slot);
		hub_lua->ajouter_element(&h_ticinput);
		hub_lua->ajouter_element(&h_2D);
		hub_lua->ajouter_element(&h_3D);
		hub_lua->ajouter_element(scene_opengl);

		P101_Cubix::BlocMap * p_map = new P101_Cubix::BlocMap();
		hub_lua->lib_ajouter("map", p_map);

		Bloc * p_bloc_test = new Bloc();
		p_bloc_test->nom = "bloc";
		p_bloc_test->texture = "DATA/Textures/alpha.png";
		p_bloc_test->fragmentShader = "DATA/Shaders/texture.frag";
		p_bloc_test->vertexShader = "DATA/Shaders/texture.vert";
		hub_lua->lib_ajouter("bloc", p_bloc_test);

		ogli::BLutin * blutin = new ogli::BLutin();
		blutin->texture = "DATA/Textures/alpha.png";
		blutin->vertexShader = "DATA/Shaders/texture2Dp.vert";
		blutin->fragmentShader = "DATA/Shaders/texture2Dp.frag";
		hub_lua->lib_ajouter("blutin", blutin);

		ogli::Lutin_BTexte * tlutin = new ogli::Lutin_BTexte;
		tlutin->texture = "DATA/Textures/font2.png";
		tlutin->texte = "Test";
		tlutin->vertexShader = "DATA/Shaders/texture2Dp.vert";
		tlutin->fragmentShader = "DATA/Shaders/texture2Dp.frag";
		hub_lua->lib_ajouter("tlutin", tlutin);

		cmd_s = new cmd_slot(h_2D, input);
		h_slot.push("cmd_s", cmd_s);
		h_ticinput.push("cmd_s", cmd_s);

		// LUA
		env->Exec("config.lua");
	}

	void mainsys()
	{
		while (!input.terminer())
		{
			input.updateEvenements();
			if (input.getTouche(SDL_SCANCODE_ESCAPE))
				break;

			dt_mainsys->actualiser();
			h_ticinput.actualiser();
			h_slot.actualiser();
			scene_opengl->tic();

			if (dt_mainsys->Delta_t < target)
				SDL_Delay(target - dt_mainsys->Delta_t);
		}
	}

protected:
	Uint32 target;

	ogli::hub_Slot h_slot;
	ogli::hub_TicInput h_ticinput;
	ogli::hub_2D h_2D;
	gen::hub_3D h_3D;

	cmd_slot * cmd_s;

	Input input;
	SceneOpenGL * scene_opengl;
};

#endif