#version 330

uniform mat4 Transform;

in vec4 vPosition;
in vec2 vTexCoord;

out vec2 vUV;

void main() 
{
  gl_Position = Transform*vPosition;

  vUV = vTexCoord;
} 
