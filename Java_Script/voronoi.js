var MAX = 100000;

/**
 * Objet cellule
 * une cellule du diagramme de Voronoi
 * contient l'ensemble des sommets de
 * la region convexe delimitee par cette
 * cellule ainsi que les cellules qui lui
 * sont adjacent.
 */
function cellule(id) {
	this.point = new point(0, 0);
	this.id = id;

	// ensemble des sommets constituants
	// la cellule (/region) de Voronoi
	this.sommets   = [];
	this.nbSommets = 0;
	// ensemble des cellules adjacentes
	// a la cellule courante
	// this.adjacents[i] est la cellule
	// adjacente a la cellule courante
	// et separee grace au segment
	// this.sommets[i] - this.sommets[i+1]
	this.adjacents = [];
}

/**
 * MÃ©thode distanceTo
 * renvoie la distance du point
 * a la cellule
 */
cellule.prototype.distanceTo = function(pt) {
	return pt.distanceTo(this.point);
};

function equalCells(cell1, cell2) {
	return cell1 == cell2;
}

/**
 * Objet voronoi
 * diagramme de Voronoi
 */
function voronoi() {
	this.width  = 0;
	this.height = 0;

	this.cellules = [];
	this.nbPoints = 0;
}


/**
 * MÃ©thode init
 * initialise le diagramme de Voronoi
 * avec les tailles de celui-ci
 */
voronoi.prototype.init = function(width, height) {
	this.width  = width;
	this.height = height;

	// les 4 extremitees du canvas
	this.nbPoints = 4;
	var hg = this.cellules[0] = new cellule(0);
	var hd = this.cellules[1] = new cellule(1);
	var bd = this.cellules[2] = new cellule(2);
	var bg = this.cellules[3] = new cellule(3);
	hg.point = new point(-2*this.width,  -2*this.height);
	hd.point = new point(3*this.width,   -2*this.height);
	bd.point = new point(3*this.width,   3*this.height);
	bg.point = new point(-2*this.width,  3*this.height);
	hg.sommets = [
		new point(this.width/2, -MAX),
		new point(this.width/2, this.height/2),
		new point(-MAX,         this.height/2)
	];
	hd.sommets = [
		new point(this.width/2, -MAX),
		new point(MAX,          this.height/2),
		new point(this.width/2, this.height/2)
	];
	bd.sommets = [
		new point(this.width/2, this.height/2),
		new point(MAX,          this.height/2),
		new point(this.width/2, MAX)
	];
	bg.sommets = [
		new point(-MAX,         this.height/2),
		new point(this.width/2, this.height/2),
		new point(this.width/2, MAX)
	];
	hg.nbSommets = hd.nbSommets = bd.nbSommets = bg.nbSommets = 3;
	hg.adjacents = [hd, bg, null];
	hd.adjacents = [null, bd, hg];
	bd.adjacents = [hd, null, bg];
	bg.adjacents = [hg, bd, null];
};

/**
 * MÃ©thode whichCell
 * renvoie la cellule du diagramme de
 * Voronoi contenant le point pt.
 */
voronoi.prototype.whichCell = function(pt) {
	var dmin = Number.MAX_VALUE;
	var cellmin = null;
	for(var i = 0; i < this.nbPoints; i++) {
		var tmp = this.cellules[i].distanceTo(pt);
		if(tmp < dmin) {
			dmin = tmp;
			cellmin = this.cellules[i];
		}
	}
	return cellmin;
};

/**
 * Fonction auxiliaire pour la fabrication
 * des nouvelles cellules a l'ajout de points
 */
function cutCell(cell, newcell) {
	// la mÃ©diatrice
	var med = mediatrice(cell.point, newcell.point);
	// determination des (2!) points d'intersection
	var itscs = intersectionDroitePolygone(cell.sommets, med);
	var ips  = itscs.ips;
	var nums = itscs.nums;
	var firstAdj = cell.adjacents[nums[0]];
	var lastAdj  = cell.adjacents[nums[1]];

	// on determine les nouveaux sommets de la cellule
	var tmp_sommets = cell.sommets.splice(
		nums[0]+1, nums[1]-nums[0], ips[0], ips[1]);
	var tmp_adjacents = cell.adjacents.splice(
		nums[0]+1, nums[1]-nums[0], newcell, lastAdj);
	// on verifie de quel cote de la cellule coupe
	// en deux on garde pour elle meme
	var d1 = newcell.distanceTo(cell.sommets[0]);
	var d2 = cell.distanceTo(cell.sommets[0]);
	if(d2 > d1) {
		cell.sommets = tmp_sommets;
		cell.sommets.unshift(ips[0]);
		cell.sommets.push(ips[1]);
		cell.adjacents = tmp_adjacents;
		cell.adjacents.unshift(firstAdj);
		cell.adjacents.push(newcell);
	}
	cell.nbSommets = cell.sommets.length;

	return {ips: ips, adjacents: [firstAdj, lastAdj]};
}

/**
 * MÃ©thode addPoint
 * ajoute un point sur la carte, le diagramme
 * de Voronoi est mis Ã  jour en consÃ©quence
 * cout en O(n) avec n le nombre de point
 * existant deja sur le diagramme.
 * Creation d'un diagramme a n points en O(n^2)
 */
voronoi.prototype.addPoint = function(pt) {

	// on dÃ©termine dans quelle cellule
	// dÃ©jÃ  crÃ©e le point se trouve
	var cellmin = this.whichCell(pt);
	if(pt.x == cellmin.point.x && pt.y == cellmin.point.y) return;

	// on crÃ©e une nouvelle cellule
	var cell = this.cellules[this.nbPoints] = new cellule(this.nbPoints);
	cell.point = pt;
	
	// on coupe en deux la cellule obtenu
	// selon la mÃ©diatrice entre le point
	// courant et le point de la cellule

	var tmp = cutCell(cellmin, cell);
	var ips = tmp.ips;
	var first = tmp.adjacents[0];
	var last  = tmp.adjacents[1];

	// on determine la cellule pour le nouveau point
	cell.sommets.push(ips[0].copy());
	cell.adjacents.push(first);
	var prec = cellmin;
	var suivant = first;
	while(!equalCells(suivant, last)) {
		tmp = cutCell(suivant, cell);
		var adj = tmp.adjacents;

		var prec_tmp = suivant;
		var num = equalCells(prec, tmp.adjacents[0]) ? 1 : 0;
		suivant = tmp.adjacents[num];
		prec = prec_tmp;

		cell.sommets.push(tmp.ips[num].copy());
		cell.adjacents.push(suivant);
	}
	cutCell(suivant, cell);
	cell.sommets.push(ips[1].copy());
	cell.adjacents.push(cellmin);

	cell.nbSommets = cell.sommets.length;

	this.nbPoints++;
};

/**
 * MÃ©thode render
 * affiche le diagramme de Voronoi
 * dans le canvas passe en parametre
 */
voronoi.prototype.render = function(ctx) {
	if(this.nbPoints == 0) return;

	ctx.beginPath();
	for(var i = 4; i < this.nbPoints; i++) {
		var cell = this.cellules[i];
		var pos = cell.sommets[0];
		ctx.moveTo(pos.x, pos.y);
		for(var j = 1; j < cell.nbSommets; j++) {
			pos = cell.sommets[j];
			ctx.lineTo(pos.x, pos.y);
		}
		ctx.closePath();
	}
	ctx.stroke();

	ctx.beginPath();
	for(var i = 4; i < this.nbPoints; i++) {
		var cell = this.cellules[i];
		var pos = cell.point;
		ctx.moveTo(pos.x, pos.y);
		ctx.arc(pos.x, pos.y, 2, 0, 2*Math.PI);
	}
	ctx.fill();
};



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