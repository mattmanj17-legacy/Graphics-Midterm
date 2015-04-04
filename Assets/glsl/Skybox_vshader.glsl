#version 330
in  vec4 vPosition;
in  vec4 Normal;

uniform mat4 ModelView;

out vec3 R;

void main()
{
    gl_Position = ModelView*vPosition;

	R = Normal.xyz;
}
