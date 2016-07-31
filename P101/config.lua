map_nadr = sbl_getcible()
--dofile('.\DATA\main.lua')


bloc_nadr = sbl_create('bloc')
sbl_charger(bloc_nadr)
sbl_set('texture', 'DATA/Textures/Herbe.jpg')
sbl_set('nom', 'bloc herbe')
sbl_exec('charger')
sbl_fermer()

sbl_charger(map_nadr)
sbl_exec('ajouterBlocIndex', bloc_nadr)
sbl_exec('ajouterBlocMap', 'bloc herbe', 25, 25, 25)
sbl_fermer(map_nadr)