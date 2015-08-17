#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "texture.h"

#define GL_CHECK_ERRORS \
{ \
	int err=glGetError(); \
	if (err!=0) \
	{   cout << "OpenGL Error: " << err << endl; \
		assert(err == GL_NO_ERROR); \
	} \
}

int currentTextureUnit = GL_TEXTURE1;

class Texture2D
{
private:
	GLuint textureUnit;
	char* fileName;

public:
	GLuint id;

	Texture2D(char* fName)
	{
		fileName = fName;
		glActiveTexture(currentTextureUnit);
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		textureUnit = MyLoadBitmap(fileName, GL_TEXTURE_2D , true);
		GL_CHECK_ERRORS
	}

	~Texture2D()
	{
		glDeleteTextures(1, &id );
	}
};

#endif