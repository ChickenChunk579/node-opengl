const glfw = require("./glfw");
const gl = require("./opengl");
const process = require('node:process');


const COLOR_BUFFER_BIT = 0x00004000;
const FLOAT = 0x1406;
const FALSE = 0x0;
const VERTEX_SHADER = 0x8B31;
const FRAGMENT_SHADER = 0x8B30;
const TRIANGLES = 0x0004;

if (!glfw.init()) {
    console.log("Failed to initialize GLFW!");

    glfw.terminate();

    process.exit(1);
}

let major = glfw.getVersionMajor();
let minor = glfw.getVersionMinor();
let rev = glfw.getVersionRev();

console.log(`GLFW ${major}.${minor}r${rev}`);

glfw.createWindow("PROJECT NOVA", 1280, 720);

glfw.makeContextCurrent();

console.log("Made OpenGL context current");

gl.load();

console.log("Loaded OpenGL");

let vertices = new Float32Array([
    -0.5, -0.5, 0.0,
    0.5, -0.5, 0.0,
    0.0, 0.5, 0.0
]);


let fragmentShaderSource = `
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
`;

let vertexShaderSource = `
#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
`

let vbo = gl.createBuffer();
console.log("Created VBO");
gl.bufferData(vbo, vertices, 36);
console.log("Filled VBO");

let vao = gl.createVertexArray();
gl.vertexAttribPointer(vao, vbo, 0, 3, FLOAT, FALSE, 3 * 4, 0)


let vertexShader = gl.createShader(vertexShaderSource, VERTEX_SHADER);
let fragmentShader = gl.createShader(fragmentShaderSource, FRAGMENT_SHADER);
let program = gl.createProgram(vertexShader, fragmentShader);

console.log(`Program: ${program}\nvao: ${vao}`);

while (!glfw.windowShouldClose()) {
    gl.clearColor(1.0, 1.0, 1.0, 1.0);
    gl.clear(COLOR_BUFFER_BIT);

    gl.bindVertexArray(vao);
    gl.useProgram(program);

    gl.drawArrays(TRIANGLES, 0, 3);

    glfw.pollEvents();
    glfw.swapBuffers();
}

glfw.destroyWindow();

glfw.terminate();