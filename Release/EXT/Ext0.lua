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
-- 


-- Function to simplify creation of bloc on graphic interface
function placebloc(nombloc,x,y,z)
sbl_charger(map_nadr)
sbl_exec('ajouterBlocMap', nombloc, x,z,y)
sbl_fermer(map_nadr)
end
--