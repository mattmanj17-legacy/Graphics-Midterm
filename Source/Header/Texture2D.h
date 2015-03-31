#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "texture.h"

int textureNum = GL_TEXTURE1;

class Texture2D
{
private:
	GLuint thisTexture;
	char* fileName;

	~Texture2D()
	{
		glDeleteTextures(1, &texid );
	}
public:
	GLuint texid;

	Texture2D(char* fName)
	{
		fileName = fName;
		thisTexture = textureNum++;
		glActiveTexture(thisTexture);
		glGenTextures(1, &texid);
		glBindTexture(GL_TEXTURE_2D, texid);
		MyLoadBitmap(fileName, GL_TEXTURE_2D , true);
	}

	void setActive()
	{
		glEnable(GL_TEXTURE_2D);
		glActiveTexture(thisTexture);
		glBindTexture(GL_TEXTURE_2D, texid);

		glEnable(GL_BLEND);
	    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	    // Prevent alpha values of less than 0.1 from writing out the the depth test buffer.
	    glAlphaFunc ( GL_GREATER, 0.1 ) ;
        glEnable ( GL_ALPHA_TEST ) ;
	}
};

#endif