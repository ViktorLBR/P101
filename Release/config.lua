-- 	[config.lua]
-- 	Réservé équipe C++, équipe lua => modifier [main.lua]
-- 	Pour SBL 1.1b
--	
--	Projet P101, version release
--	
--
--	      ___
--	     / \ \
--	    /  /\ \
--	   /  /  \ \
--	  /  /____\ \
--	 /_________\_\
--
--	The Delta Team


-- Récupération 'SceneOpenGL'
opengl_nadr = sbl_getnom('SceneOpenGL')
sbl_charger(opengl_nadr)


-- Chargement de la map sur map_nadr
map_nadr = sbl_create('map')
sbl_exec('pushdisp', map_nadr)
sbl_fermer()


-- Exécution de [main.lua]

dofile('Ext/ExtMain.lua')
dofile('DATA/main.lua')

