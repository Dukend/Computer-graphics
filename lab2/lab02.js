'By Dukend'
new p5();
let WIDTH = 1500, HEIGHT = 1000;
function drawPiramid(h, R, x, y, z) {
	let n = document.getElementById('n_number_of_sides').value;
	if (n < 3) {
		return;
	}
	let arr = []
	for (let i = 0; i < n; i++) {
		arr.push({ x: cos(i * 2 * PI / n) * R + (x || 0), y: 0 + (y || 0), z: -(sin(i * 2 * PI / n) * R) + (z || 0) })
	}

	let top_point = { x: 0 + (x || 0), y: - h + (y || 0), z: 0 + (z || 0) };

	beginShape(TRIANGLES);
	vertex(top_point.x, top_point.y, top_point.z);
	vertex(arr[arr.length - 1].x, arr[arr.length - 1].y, arr[arr.length - 1].z);
	vertex(arr[0].x, arr[0].y, arr[0].z);
	endShape();

	for (let i = 1; i < n; i++) {
		beginShape(TRIANGLES);
		vertex(top_point.x, top_point.y, top_point.z);
		vertex(arr[i - 1].x, arr[i - 1].y, arr[i - 1].z);
		vertex(arr[i].x, arr[i].y, arr[i].z);
		endShape();
	}
	beginShape();
	for (let i = 0; i < n; i++) {
		vertex(arr[i].x, arr[i].y, arr[i].z);
	}
	endShape(CLOSE);
}
function setup() {
	createCanvas(WIDTH, HEIGHT, WEBGL);
	background(255);
	debugMode();
}

function draw() {
	background(255);
	ambientLight(128, 128, 128);
	directionalLight(128, 128, 128, 100, -100, 0);
	ambientMaterial(255);
	orbitControl();
	push();
	drawPiramid(300, 200, 0, -20, 0);
	pop();
}
