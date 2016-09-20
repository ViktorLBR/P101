opengl_s = sbl_getnom('SceneOpenGL')
h_slot_nadr = sbl_getnom('hub_Slot')
h_ticinput_nadr = sbl_getnom('hub_TicInput')
h_2D_nadr = sbl_getnom('hub_2D')
h_3D_nadr = sbl_getnom('hub_3D')




map_nadr = sbl_create('map')
sbl_charger(h_3D_nadr)
sbl_exec('push', 'map', map_nadr)
sbl_fermer()




function tcallback()
 vart = sbl_get('texte')
 if vart == 'ok' then
  sbl_set('texte', 'test')
 else
  sbl_set('texte', 'ok')
 end
 sbl_exec('charger')
end

function callback()
 x, y = sbl_get('coord')
 sbl_set('coord', x+y+0.01, y-x, 0.5)
 sbl_exec('charger')
end

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
sbl_set('coord', 0.2, 0, 0.5)
sbl_exec('charger')
sbl_exec('enregistrerFonc', 'onClic', 'callback')
sbl_set('nom','testblutin')
sbl_set('visible', 1)

sbl_fermer()


texte_nadr = sbl_create('tlutin')
sbl_charger(texte_nadr)

sbl_set('dim', 0.05, 0.3)
sbl_set('coord', 0.1, 0, 0.05)
sbl_exec('enregistrerFonc', 'onClic', 'tcallback')
sbl_exec('link', blutin_nadr)
sbl_set('nom','testtlutin')
sbl_set('visible', 1)
sbl_exec('charger')

sbl_fermer()

sbl_charger(h_ticinput_nadr)
sbl_exec('push', 'blutin', blutin_nadr)
sbl_exec('push', 'tlutin', texte_nadr)

sbl_charger(h_2D_nadr)
sbl_exec('push', 'blutin', blutin_nadr)
sbl_exec('push', 'tlutin', texte_nadr)

sbl_fermer(blutin_nadr)


