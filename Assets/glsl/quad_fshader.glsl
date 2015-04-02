#version 330

uniform sampler2D Tex;

in vec2 vUV;

out vec4 fColor;

void main()
{
	fColor = texture(Tex,vUV);
	//fColor = vec4(1.0,0.0,0.0,1.0);
}
