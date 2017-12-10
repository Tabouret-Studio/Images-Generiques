#version 330

layout(location = 1) in vec2 aVertexPosition;

out vec3 vColor;

void main() {
    vColor = vec3(1, 1, 1);
    gl_Position = vec4(aVertexPosition, 0, 1);
}
