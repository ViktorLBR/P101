map_nadr = sbl_getcible()

bloc_nadr = sbl_create('bloc')

sbl_exec('ajouterBlocIndex', bloc_nadr)
sbl_exec('ajouterBlocMap', 'bloc', 25, 25, 25)

sbl_fermer(map_nadr)