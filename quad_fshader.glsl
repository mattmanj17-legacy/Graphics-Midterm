#version 150

uniform sampler2D texMap;

in vec2 vSR;

out vec4 fColor;

void main()
{
	fColor = texture(texMap, vSR);
}
