-- Function to simplify bloc initialisation
function blocinit(nombloc,texturepath,bloc_nadr)
bloc_nadr = sbl_create('bloc')

sbl_charger(bloc_nadr)

sbl_set('texture', texturepath)

sbl_set('nom', nombloc)

sbl_exec('charger')

sbl_fermer()
sbl_charger(map_nadr)
sbl_exec('ajouterBlocIndex', bloc_nadr)
sbl_fermer(map_nadr)
end

-- Function to simplify creation of bloc on graphic interface
function placebloc(bloc_nadr_id,nombloc,x,y,z)
sbl_charger(map_nadr)
sbl_exec('ajouterBlocMap', nombloc, x,z,y)
sbl_fermer(map_nadr)
end

-- Code starts here
blocinit('bloc_herbe','DATA/Textures/Herbe.jpg',bloc_herbe_nadr)
placebloc(bloc_herbe_nadr,'bloc_herbe',25,25,25)
blocinit('bloc_caisse','DATA/Textures/Caisse.jpg',bloc_caisse_nadr)
placebloc(bloc_caisse_nadr,'bloc_caisse',25,25,26)