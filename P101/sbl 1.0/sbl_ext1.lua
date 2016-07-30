-- sbl_ext1 pour sbl 1.0





-- sbl_setnom()
function sbl_setnom(nom)
	sbl_set('nom', nom)
end


-- sbl_getnom()
function sbl_getnom()
	return sbl_get('nom')
end


-- sblx1_get()
function sblx1_get(nadrp, var)
	nadr = sbl_getcible()
	sbl_charger(nadrp) 
	r = sbl_get(var)
	sbl_charger(nadr)
	return r
end


-- sblx1_set()
function sblx1_set(narpd, var, val)
	nadr = sbl_getcible()
	sbl_charger(nadrp) 
	sbl_set(var, val)
	sbl_charger(nadr)
end


-- sblx1_exec()
function sblx1_exec(narpd, f)
	nadr = sbl_getcible()
	sbl_charger(nadrp) 
	r = sbl_exec(f)
	sbl_charger(nadr)
	return r
end


-- sbl_new()
function sbl_new(nom)
	nadr = sbl_create(nom)
	sbl_charger(nadr)
end
function sbl_new(nom, nome)
	sbl_new(nom)
	sbl_setnom(nome)
end