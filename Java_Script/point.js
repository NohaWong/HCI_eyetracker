/**
 * Objet point
 */
function point(x, y) {
	this.x = x;
	this.y = y;
}

/**
 * Methode copy
 * renvoie une copie du point
 */
point.prototype.copy = function() {
	return new point(this.x, this.y);
};

/**
 * Methode distanceTo
 * renvoie la distance du point
 * courant au point passe en parametre
 */
point.prototype.distanceTo = function(pt) {
	var dx = this.x - pt.x;
	var dy = this.y - pt.y;
	return Math.sqrt(dx*dx + dy*dy);
};

/**
 * Fonction perProduct
 * renvoie le produit scalaire entre
 * les vecteurs (=point) pt1 et un
 * vecteur orthogonal a pt2.
 */
function perProduct(pt1, pt2) {
	return pt1.x*pt2.y - pt1.x*pt2.y;
};

/**
 * Fonction mediatrice
 * renvoie une equation cartesienne
 * de la forme ax + by + c = 0
 * de la mediatrice des points pt1
 * et pt2.
 */
function mediatrice(pt1, pt2) {
	var tmp = {a: 0, b: 0, c: 0};
	var milieu = new point((pt1.x + pt2.x)/2, (pt1.y + pt2.y)/2);
	tmp.a = pt2.x - pt1.x;
	tmp.b = pt2.y - pt1.y;
	tmp.c = -(tmp.b*milieu.y + tmp.a*milieu.x);
	return tmp;
}

/**
 * Fonction intersectionDroitePolygone
 * renvoie les points d'intersection entre la droite
 * et le polygone represente par l'ensemble de ses
 * sommets.
 * renvoie aussi les numeros i des points tel que
 * les points d'intersection se trouvent entre i et i+1
 */
function intersectionDroitePolygone(lstPts, droite) {
	// Les points d'intersection
	var ptsIntersect = [];
	var numPts = [];
	var lastPt = lstPts[0];
	var nbPts = lstPts.length;
	for(var i = 0; i < nbPts; i++) {
		var currentPt = lstPts[(i + 1) % nbPts];
		// le segment de droite que l'on considÃ¨re est de
		// la forme (t*(cx - lx) + lx, t*(cy - ly) + ly)
		// avec t dans [0, 1]
		var segment = new point(currentPt.x-lastPt.x, currentPt.y-lastPt.y);
		// par identification entre les deux equations de droite
		// on dÃ©termine le moment d'intersection t qui doit Ãªtre
		// dans [0, 1]
		var num   = droite.c + droite.a*lastPt.x + droite.b*lastPt.y;
		var denom = droite.a*segment.x + droite.b*segment.y;
		var t = - num / denom;
		// si le point d'intersection est bien sur le segment
		if(t >= 0 && t <= 1) {
			// on calcul le point d'intersection
			var ipx = t*segment.x + lastPt.x;
			var ipy = t*segment.y + lastPt.y;
			ptsIntersect.push(new point(ipx, ipy));
			numPts.push(i);
		}
		lastPt = currentPt;
	}
	return {ips:ptsIntersect, nums:numPts};
}
