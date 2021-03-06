#version 330 core

layout(location = 0) in vec3 vertexPosition;

uniform mat4 mvpMatrix;

void main() {
  gl_Position = mvpMatrix * vec4(vertexPosition, 1);
}
