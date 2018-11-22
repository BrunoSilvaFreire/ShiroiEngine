#version 330 core

layout(location = 0) in vec4 vertexPosition;
uniform mat4 mvpMatrix;
void main() {
  gl_Position.xyz = vertexPosition.xyz;
  gl_Position.w = 1.0;
}
