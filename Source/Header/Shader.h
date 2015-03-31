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
	~Shader()
	{
		glDeleteProgram(id);
	}
public:
	string vShader;
	string fShader;
	
	GLuint transformAttribute;
	GLuint textureAttribute;

	GLuint positionBuffer;
	GLuint normalBuffer;
	GLuint texCoordBuffer;

	GLuint id;
	
	void init()
	{
		id  = InitShader(vShader.c_str(), fShader.c_str());
		GL_CHECK_ERRORS

		transformAttribute = glGetAttribLocation(id, "Transform");	
		textureAttribute = glGetAttribLocation(id, "Tex"); 

		positionBuffer = glGetAttribLocation(id, "vPosition"); 
		normalBuffer = glGetUniformLocation(id, "vNormal");
		texCoordBuffer = glGetUniformLocation(id, "vTexCoord");
		GL_CHECK_ERRORS
	}

	void setActive()
	{
		glUseProgram(id);
		GL_CHECK_ERRORS
	}
};

#endif