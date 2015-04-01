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
	GLuint vNormalAtribId;
	GLuint vTexCoordAtribId;

	GLuint id;
	
	Shader(string v, string f)
	{
		vShader = v;
		fShader = f;
		
		id  = InitShader(vShader.c_str(), fShader.c_str());
		GL_CHECK_ERRORS
		glUseProgram(id);
		GL_CHECK_ERRORS

		transformAtribId = glGetUniformLocation(id, "Transform");
		GL_CHECK_ERRORS
		textureAtribId = glGetUniformLocation(id, "Tex");
		GL_CHECK_ERRORS

		vPositionAtribId = glGetAttribLocation(id, "vPosition");
		GL_CHECK_ERRORS
		vNormalAtribId = glGetUniformLocation(id, "vNormal");
		GL_CHECK_ERRORS
		vTexCoordAtribId = glGetUniformLocation(id, "vTexCoord");
		GL_CHECK_ERRORS
	}

	~Shader()
	{
		glDeleteProgram(id);
	}
};

#endif