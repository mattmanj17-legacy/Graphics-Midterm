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
		GL_CHECK_ERRORS
		glGenTextures(1, &id);
		GL_CHECK_ERRORS
		glBindTexture(GL_TEXTURE_2D, id);
		GL_CHECK_ERRORS
		textureUnit = MyLoadBitmap(fileName, GL_TEXTURE_2D , true);
		GL_CHECK_ERRORS
	}

	void setActive()
	{
		glEnable(GL_TEXTURE_2D);
		glActiveTexture(textureUnit);
		GL_CHECK_ERRORS
		glBindTexture(GL_TEXTURE_2D, id);
		GL_CHECK_ERRORS

		glEnable(GL_BLEND);
	    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	    // Prevent alpha values of less than 0.1 from writing out the the depth test buffer.
	    glAlphaFunc ( GL_GREATER, 0.1 ) ;
        glEnable ( GL_ALPHA_TEST ) ;
	}

	~Texture2D()
	{
		glDeleteTextures(1, &id );
	}
};

#endif