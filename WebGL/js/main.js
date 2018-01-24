// zmienne globalne
var gl_canvas;
var gl_ctx;

var _position;
var _color;

var _triangleVertexBuffer;
var _triangleFacesBuffer;

// funkcja główna
function runWebGL () {
	gl_canvas = document.getElementById("glcanvas");
	gl_ctx = gl_getContext(gl_canvas);
	gl_initShaders();
	gl_initBuffers();
	gl_draw();
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
    attribute vec3 color;\n\
    varying vec3 vColor;\n\
    void main(void) {\n\
       gl_Position = vec4(position, 0., 1.);\n\
       vColor = color;\n\
    }";

	var fragmentShader = "\n\
      precision mediump float;\n\
      varying vec3 vColor;\n\
      void main(void) {\n\
         gl_FragColor = vec4(vColor, 1.);\n\
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
	_color = gl_ctx.getAttribLocation(shaderProgram, "color");
	gl_ctx.enableVertexAttribArray(_position);
	gl_ctx.enableVertexAttribArray(_color);
	gl_ctx.useProgram(shaderProgram);
}

// bufory
function gl_initBuffers () {
	var triangleVertices = [
		-1, -1,
		0, 0, 1,
		1, -1,
		1, 1, 1,
		1, 1,
		1, 0, 0
	];

	_triangleVertexBuffer = gl_ctx.createBuffer();
	gl_ctx.bindBuffer(gl_ctx.ARRAY_BUFFER, _triangleVertexBuffer);
	gl_ctx.bufferData(gl_ctx.ARRAY_BUFFER,
		new Float32Array(triangleVertices),
		gl_ctx.STATIC_DRAW);

	var triangleFaces = [0, 1, 2];

	_triangleFacesBuffer = gl_ctx.createBuffer();
	gl_ctx.bindBuffer(gl_ctx.ELEMENT_ARRAY_BUFFER, _triangleFacesBuffer);
	gl_ctx.bufferData(gl_ctx.ELEMENT_ARRAY_BUFFER,
		new Uint16Array(triangleFaces),
		gl_ctx.STATIC_DRAW);
}

// rysowanie
function gl_draw() {
	gl_ctx.clearColor(0.0, 0.0, 0.0, 0.0);

	var animate = function () {
		gl_ctx.viewport(0.0, 0.0, gl_canvas.width, gl_canvas.height);
		gl_ctx.clear(gl_ctx.COLOR_BUFFER_BIT);

		gl_ctx.vertexAttribPointer(_position, 2, gl_ctx.FLOAT, false, 4*(2+3), 0);
		gl_ctx.vertexAttribPointer(_color, 3, gl_ctx.FLOAT, false, 4*(2+3), 2*4);

		gl_ctx.bindBuffer(gl_ctx.ARRAY_BUFFER, _triangleVertexBuffer);
		gl_ctx.bindBuffer(gl_ctx.ELEMENT_ARRAY_BUFFER, _triangleFacesBuffer);

		gl_ctx.drawElements(gl_ctx.TRIANGLES, 3, gl_ctx.UNSIGNED_SHORT, 0);
		gl_ctx.flush();
	};
	animate();
}