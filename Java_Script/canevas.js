/**
 * Objet canvas
 * objet permettant de creer et de
 * manipuler plus facilement un canvas HTML5.
 */
function canvas() {
	this.width  = 0;
	this.height = 0;
	this.cvs = document.createElement("canvas");
	this.ctx = this.cvs.getContext("2d");

	this.xmin = [];
	this.xmax = [];
	this.ymin = [];
	this.ymax = [];
	this.nbClear = 0;
}

/**
 * Methode init
 * initialise la taille du canvas
 */
canvas.prototype.init = function(w, h) {
	this.width  = w;
	this.height = h;
	this.cvs.width  = w;
	this.cvs.height = h;
	this.cvs.style.width  = w+"px";
	this.cvs.style.height = h+"px";
}

/**
 * Methode append
 * ajoute dans un element de la page
 * la balise canvas.
 */
canvas.prototype.append = function(domElement) {
	domElement.appendChild(this.cvs);
}

/**
 * Methode refresh
 * vide le canvas des dessins presents
 */
canvas.prototype.refresh = function() {
	this.ctx.clearRect(0, 0, this.width, this.height);
};
