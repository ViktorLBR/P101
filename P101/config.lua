opengl_s = sbl_getnom('SceneOpenGL')
map_nadr = sbl_create('map')

h_slot_nadr = sbl_getnom('hub_Slot')
h_ticinput_nadr = sbl_getnom('hub_TicInput')
h_2D_nadr = sbl_getnom('hub_2D')

sbl_charger(opengl_s)
sbl_exec('pushdisp', map_nadr)
sbl_fermer()

function tcallback()
 sbl_exec('charger')
end

function callback()
 x, y = sbl_get('coord')
 sbl_set('coord', x+y+0.01, y-x, 0.1)
 sbl_exec('charger')
end



texte_nadr = sbl_create('tlutin')
sbl_charger(texte_nadr)

sbl_set('dim', 0.3, 1)
sbl_set('coord', -0.8, -0.6, 0.1)
sbl_exec('enregistrerFonc', 'onClic', 'tcallback')
sbl_set('nom','testtlutin')
sbl_set('visible', 1)
sbl_exec('charger')

sbl_fermer()


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
blutin_nadr = sbl_create("blutin")
sbl_charger(blutin_nadr)

sbl_set('dim', 0.1, 0.1)
sbl_exec('charger')
sbl_exec('enregistrerFonc', 'onClic', 'callback')
sbl_set('nom','testblutin')
sbl_set('visible', 1)


sbl_charger(h_ticinput_nadr)
sbl_exec('push', 'blutin', blutin_nadr)
sbl_exec('push', 'tlutin', texte_nadr)

sbl_charger(h_2D_nadr)
sbl_exec('push', 'tlutin', texte_nadr)
sbl_exec('push', 'blutin', blutin_nadr)

sbl_fermer(blutin_nadr)


