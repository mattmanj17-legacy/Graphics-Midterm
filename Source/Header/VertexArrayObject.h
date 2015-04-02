#ifndef VERTEXARRAYOBJECT_H
#define VERTEXARRAYOBJECT_H

#include <iostream>
#include <cmath>
#include <iomanip>
#include <cassert>
#include <vector>
using namespace std;

#include <GL/glew.h> // for OpenGL extensions
#include <GL/glut.h> // for Glut utility kit

#include "Shader.h"
#include "TriMesh.h"
#include "Texture2D.h"
#include "Transform.h"
#include "Camera.h"

#define GL_CHECK_ERRORS \
{ \
	int err=glGetError(); \
	if (err!=0) \
	{   cout << "OpenGL Error: " << err << endl; \
		assert(err == GL_NO_ERROR); \
	} \
}

class VertexArrayObject
{
private:
	Shader* program;
	Texture2D* texture;
	TriMesh* mesh;

	GLuint vao;
	GLuint positionBuffer_id;
	GLuint texCoordBuffer_id;

public:
	Transform transform;

	VertexArrayObject(TriMesh* Mesh, Texture2D* Texture, Shader* Program)
	{
		mesh = Mesh;
		texture = Texture;
		program = Program;
		
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		GL_CHECK_ERRORS

		glUseProgram(program->id);

		// fill position buffer from mesh
		glGenBuffers(1, &positionBuffer_id);
		glBindBuffer(GL_ARRAY_BUFFER, positionBuffer_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * mesh->size(), &(mesh->positions[0]), GL_STATIC_DRAW);
		GL_CHECK_ERRORS
		// attach buffer to correct vertex attribute
		glVertexAttribPointer(program->vPositionAtribId, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(program->vPositionAtribId);
		GL_CHECK_ERRORS

		// fill texCoord buffer from mesh
		glGenBuffers(1, &texCoordBuffer_id);
		glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * mesh->size(), &(mesh->texCoords[0]), GL_STATIC_DRAW);
		GL_CHECK_ERRORS
		// attach buffer to correct vertex attribute
		glVertexAttribPointer(program->vTexCoordAtribId, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(program->vTexCoordAtribId);
		GL_CHECK_ERRORS

		//ship texture2d data
		glUniform1i(program->textureAtribId, texture->id);
		GL_CHECK_ERRORS
	}

	void draw()
	{
		glBindVertexArray( vao );
		glUseProgram(program->id);
		texture->setActive();

		glEnable(GL_DEPTH_TEST);

		glUniformMatrix4fv( program->transformAtribId, 1, GL_TRUE, Camera::GetInstance()->GetCameraMatrix() * transform.getTransformMatrix() );
		
		glDrawArrays( GL_TRIANGLES, 0, mesh->size());
		GL_CHECK_ERRORS

		glUseProgram(0);
		glBindVertexArray(0);
		GL_CHECK_ERRORS
	}

	~VertexArrayObject()
	{
		glDeleteBuffers(1, &positionBuffer_id);
		glDeleteBuffers(1, &texCoordBuffer_id);
		glDeleteVertexArrays(1, &vao);
	}
};

#endif