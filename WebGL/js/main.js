// zmienne globalne
var gl_canvas;
var gl_ctx;

var _position;

// funkcja główna
function runWebGL () {
	gl_canvas = document.getElementById("glcanvas");
	gl_ctx = gl_getContext(gl_canvas);
	gl_initShaders();
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

// shadery
function gl_initShaders () {
	var vertexShader = "\n\
	attribute vec2 position;\n\
	   void main(void) {\n\
		   gl_Position = vec4(position, 0., 1.);\n\
	}";

	var fragmentShader = "\n\
	precision mediump float;\n\
	  void main(void) {\n\
		  gl_FragColor = vec4(0., 0., 0., 1.);\n\
	}";

	var getShader = function(source, type, typeString) {
		var shader = gl_ctx.createShader(type);
		gl_ctx.shaderSource(shader, source);
		gl_ctx.compileShader(shader);

		if (!gl_ctx.getShaderParameter(shader, gl_ctx.COMPILE_STATUS)) {
			alert('error in ' + typeString);
			return false;
		}
		return shader;
	};

	var shaderVertex = getShader(vertexShader, gl_ctx.VERTEX_SHADER, "VERTEX");
	var shaderFragment = getShader(fragmentShader, gl_ctx.FRAGMENT_SHADER, "FRAGMENT");

	var shaderProgram = gl_ctx.createProgram();
	gl_ctx.attachShader(shaderProgram, shaderVertex);
	gl_ctx.attachShader(shaderProgram, shaderFragment);

	gl_ctx.linkProgram(shaderProgram);
	_position = gl_ctx.getAttribLocation(shaderProgram, "position");
	gl_ctx.enableVertexAttribArray(_position);
	gl_ctx.useProgram(shaderProgram);
}