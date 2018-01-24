// zmienne globalne
var gl_canvas;
var gl_ctx;

// funkcja główna
function runWebGL () {
	gl_canvas = document.getElementById("glcanvas");
	gl_ctx = gl_getContext(gl_canvas);
	/ /gl_initShaders();
	// gl_initBuffers();
	// gl_draw();
}  

// pobranie kontekstu WebGL
function gl_getContext (canvas) {
	try {
		var ctx = canvas.getContext("webgl");
		ctx.viewportWidth = canvas.width;
		ctx.viewportHeight = canvas.height;
	} catch (e) {}
	if (!ctx) {
		document.write('Nieudana inicjalizacja kontekstu WebGL.')
	}
	return ctx;
}