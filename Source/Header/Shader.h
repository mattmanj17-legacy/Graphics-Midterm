#ifndef SHADER_H
#define SHADER_H

typedef unsigned int GLuint;

#include "Angel.h"

#define GL_CHECK_ERRORS \
{ \
	int err=glGetError(); \
	if (err!=0) \
	{   cout << "OpenGL Error: " << err << endl; \
		assert(err == GL_NO_ERROR); \
	} \
}

class Shader
{
private:
	
public:
	string vShader;
	string fShader;
	
	GLuint transformAtribId;
	GLuint textureAtribId;

	GLuint vPositionAtribId;
	GLuint vTexCoordAtribId;

	GLuint id;
	
	Shader(string v, string f)
	{
		vShader = v;
		fShader = f;
		
		id  = InitShader(vShader.c_str(), fShader.c_str());
		GL_CHECK_ERRORS

		transformAtribId = glGetUniformLocation(id, "Transform");
		textureAtribId = glGetUniformLocation(id, "Tex");

		vPositionAtribId = glGetAttribLocation(id, "vPosition");
		vTexCoordAtribId = glGetAttribLocation(id, "vTexCoord");
	}

	~Shader()
	{
		glDeleteProgram(id);
	}
};

#endif