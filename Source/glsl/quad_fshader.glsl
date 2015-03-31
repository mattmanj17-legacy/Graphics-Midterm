#version 150

uniform sampler2D Tex;

in vec2 vUV;

out vec4 fColor;

void main()
{
	fColor = texture(Tex, vUV);
}
