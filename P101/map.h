#include "stdafx.h"
#include "gen_3delement.h"

using namespace std;
using namespace gen;


#ifndef MAP_P101
#define MAP_P101

namespace P101_Cubix
{

	class BlocMap : public gen::Element3D
	{
	public:
		BlocMap()
		{
			coord = glm::vec3(-12.5,-12.5,-12.5);
			for each (Bloc * p in index_map)
				p = NULL;
		}
		~BlocMap()
		{

		}

		void ajouterBlocIndex(sblAdr nadr)
		{
			sblElement * pbloc = hub_lua->getElement(nadr);
			index_bloc.emplace(pbloc->nom, reinterpret_cast<Bloc *>(pbloc));
		}

		virtual void l_afficher(glm::mat4 &projection, glm::mat4 &modelview)
		{
			for (int x = 0; x < 100; x++)
				for (int y = 0; y < 100; y++)
					for (int z = 0; z < 100; z++)
						if (index_map[x][y][z] != NULL)
							index_map[x][y][z]->afficher(glm::vec3(x / 2, y / 2, z / 2) + coord, projection, modelview);
		}

		void ajouterBlocMap(string nom, glm::vec3 cd)
		{
			Bloc * p = reinterpret_cast<Bloc *>(index_bloc.at(nom));
			int x = cd.x * 2;
			int y = cd.y * 2;
			int z = cd.z * 2;
			index_map[x][y][z] = p;
		}

		virtual int exec(string nfonc, lua_State * L)
		{
			if (nfonc == "ajouterBlocIndex")
			{
				ajouterBlocIndex(lua_tonumber(L, 2));
				return 0;
			}
			if (nfonc == "ajouterBlocMap")
			{
				ajouterBlocMap(lua_tostring(L, 2), glm::vec3(lua_tonumber(L, 3), lua_tonumber(L, 4), lua_tonumber(L, 5)));
				return 0;
			}

			return Element3D::exec(nfonc, L);
		}

		virtual sblElement * Copie()
		{
			BlocMap * p = new BlocMap();
			HCopie(p);
			return p;
		}


	protected:
		map<string, Bloc *> index_bloc;
		Bloc * index_map[100][100][100];

		virtual void HCopie(BlocMap * p)
		{
			p->index_bloc = index_bloc;
			for (int i = 0; i < 100; i++)
				for (int j = 0; j < 100; j++)
					for (int k = 0; k < 100; k++)
						p->index_map[i][j][k] = index_map[i][j][k];

			Element3D::HCopie(p);
		}
	};

};
#endif