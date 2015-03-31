#ifndef tree_BOX_H
#define tree_BOX_H
#include "GraphicsObject.h"

typedef vec4 point4;

class TexCoords
{
private:
	float x0, x1, y0, y1;

	vector<vec2> coords;
public:
	TexCoords(){}

	TexCoords(float x0, float x1, float y0, float y1)
	{
		this->x0 = x0;
		this->x1 = x1;
		this->y0 = y0;
		this->y1 = y1;

		coords.push_back(vec2(x0, y0)); coords.push_back(vec2(x0, y0)); coords.push_back(vec2(x0, y0));
		coords.push_back(vec2(x0, y0)); coords.push_back(vec2(x0, y0)); coords.push_back(vec2(x0, y0));
	}

	vector<vec2>& getCoords()
	{
		return coords;
	}
};

class TexturedQuad : public graphics_object
{
private:
	GLuint vPosision_id;
	GLuint vPosision_id;
	GLuint vPosision_id;
public:
	string text;
	TexCoords textCoords;

	TexturedQuad(string texture, TexCoords coords) : graphics_object("texQuad") 
	{ 
		text = texture; 
		textCoords = coords;
		init();
	}

	void init_data()
	{  
		//unit quad
		quad(
			point4(-1.0, 1.0, 0.0, 1.0),
			point4(1.0, 1.0, 0.0, 1.0),
			point4(1.0, -1.0, 0.0, 1.0),
			point4(-1.0, -1.0, 0.0, 1.0)
		);
	}

	void init_VBO()
	{
		// Generate 2 buffers, one for the vertex, one for the mapCoords
		glGenBuffers(2, buffers);

		// Initialize a buffer data object of all the vertex
		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * vertex.size(), &(vertex[0]), GL_STATIC_DRAW);

		// Initialize a buffer data object of all the mapCoords
		glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(textCoords.getCoords().size()), &(textCoords.getCoords()[0]), GL_STATIC_DRAW);
		
		GL_CHECK_ERRORS
	}

	void init_shader()
	{
		program = InitShader("vshader32.glsl", "fshader32.glsl");
		glUseProgram(program);

		GL_CHECK_ERRORS

		uniforms[4] = glGetUniformLocation(program, "Transform");
		uniforms[5] = glGetUniformLocation(program, "CameraTransform");
		uniforms[5] = glGetUniformLocation(program, "Projection");
		vPosision_id = glGetAttribLocation(program, "vPosition");
		uniforms[2] = glGetAttribLocation(program, "vMapCoord");

		GL_CHECK_ERRORS

		// Buffer for the points
		glEnableVertexAttribArray(uniforms[0]);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		glVertexAttribPointer(uniforms[0], 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		GL_CHECK_ERRORS

		// Buffer for the mapcoord
		glEnableVertexAttribArray(uniforms[2]);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
		glVertexAttribPointer(uniforms[2], 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		GL_CHECK_ERRORS
	}

	void init_texture_map()
	{
		// note: separate texture loading into its own thing, and move tex map to init shader
		glActiveTexture(this_texture);
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		int TreeTex = MyLoadBitmap("trees.bmp", GL_TEXTURE_2D, true);
		GL_CHECK_ERRORS

		texMapLocation = glGetUniformLocation(program, "texMap");
		glUniform1i(texMapLocation, tex);
		GL_CHECK_ERRORS
	}

	void start_shader()
	{
		glBindVertexArray(vao);
		glUseProgram(program);

		glEnable(GL_TEXTURE_2D);
		glActiveTexture(this_texture);
		glBindTexture(GL_TEXTURE_2D, tex);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Prevent alpha values of less than 0.1 from writing out the the depth test buffer.
		glAlphaFunc(GL_GREATER, 0.1);
		glEnable(GL_ALPHA_TEST);

		// Initialize Z-Buffering
		glEnable(GL_DEPTH_TEST);
	}

	void stop_shader()
	{
		glUseProgram(0);
		glBindVertexArray(0);
		GL_CHECK_ERRORS
	}

	void draw(GLfloat theta[], vec3 translate)
	{
		start_shader();

			// ship down the new the projection and viewing matrices
			glUniformMatrix4fv(uniforms[4], 1, GL_TRUE, modelview * Translate(translate) * Scale(0.5, 0.5, 0.5) * RotateZ(theta[2]) * RotateY(theta[1]) * RotateX(theta[0]));
			GL_CHECK_ERRORS

				glUniformMatrix4fv(uniforms[5], 1, GL_TRUE, projection);
			GL_CHECK_ERRORS

			glDrawArrays(GL_TRIANGLES, 0, sizeof(tree_points) / 3);    // draw the points
			GL_CHECK_ERRORS

		stop_shader();
	}

	void cleanup()
	{
		glDeleteProgram(program);
		glDeleteTextures(1, &tex);
		glDeleteBuffers(3, buffers);
		glDeleteVertexArrays(1, &vao);
	}


};
#endif