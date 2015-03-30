#version 150

uniform mat4 Transform;
uniform mat4 CameraTransform;
uniform mat4 Projection;

in vec4 vPosition;
in vec2 vMapCoord;

out vec2 vSR;

void main() 
{
  gl_Position = Projection*CameraTransform*Transform*vPosition;

  vSR = vMapCoord;
} 
