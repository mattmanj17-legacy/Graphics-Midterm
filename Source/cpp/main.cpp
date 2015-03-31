#include <iostream>
#include <cmath>
#include <iomanip>
#include <cassert>
#include <vector>
using namespace std;

#include "Angel.h"
#include <GL/glew.h> // for OpenGL extensions
#include <GL/glut.h> // for Glut utility kit
#include "texture.h" // for the bitmap texture loader

#include "VertexArrayObject.h"
#include "Texture2D.h"
#include "Camera.h"
#include "Shader.h"
#include "TriMesh.h"
#include "Transform.h"

typedef vec4 point4;

GLfloat  zoom = 1.0;         // Translation factor

GLfloat  fovy = 60.0;		 // Field-of-view in Y direction angle (in degrees)
GLfloat  aspect = 1.0;       // Viewport aspect ratio
GLfloat  zNear = 0.5, zFar = 1000.0;

VertexArrayObject* myVAO;
TriMesh* quadMesh;
Shader* quadShader;
Texture2D* brickTexture;

void display( void )
{
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );  /*clear the window */

	Camera::GetInstance()->projection = Perspective( fovy, aspect, zNear, zFar ) * Translate( 0.0, 0.0, -zoom);

	myVAO->draw();

	glutSwapBuffers();
}

void mouse(int btn, int state, int x, int y)
{	
	glutPostRedisplay();
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
	aspect =  GLfloat (w) / h;
}

void key(unsigned char k, int x, int y)
{
    if(k == 'q') exit(0);
}

void init_gl()
{
	glEnable(GL_DEPTH_TEST);
}

void makeQuad(TriMesh* mesh, vec4 a, vec4 b, vec4 c, vec4 d)
{
	mesh->addPoint(a, vec2(0,0));
	mesh->addPoint(b, vec2(0,0));
	mesh->addPoint(c, vec2(0,0));

	mesh->addPoint(d, vec2(0,0));
	mesh->addPoint(b, vec2(0,0));
	mesh->addPoint(c, vec2(0,0));
}

void init()
{   
	init_gl();			   

	Camera::GetInstance()->projection = Perspective( fovy, aspect, zNear, zFar ) * Translate( 0.0, 0.0, -zoom);

	point4  eye( 0.0, 0.0, 0.0, -1 );
	point4  at( 0.0, 0.0, 0, 0 );
	vec4    up( 0.0, 1.0, 0.0, 0.0 );

	Camera::GetInstance()->transformMatrix = LookAt( eye, at, up );

	quadShader = new Shader("glsl/quad_vshader.glsl","glsl/quad_fshader.glsl");
	brickTexture = new Texture2D("Brick.bmp");
	quadMesh = new TriMesh();
	makeQuad(quadMesh, vec4(-0.5,0.5,0,1), vec4(0.5,0.5,0,1), vec4(0.5,-0.5,0,1), vec4(-0.5,-0.5,0,1));

	myVAO = new VertexArrayObject(quadMesh, brickTexture, quadShader);

	GL_CHECK_ERRORS
}

void OnShutdown()
{
	delete myVAO;
	delete quadMesh;
	delete quadShader;
	delete brickTexture;
}

void checkGlew()
{
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)	{
		cerr<<"Error: " << glewGetErrorString(err)<<endl;
	} else {
		if (GLEW_VERSION_3_3)
		{
			cout<<"Driver supports OpenGL 3.3\nDetails:"<<endl;
		}
	}
	cout<<"Using GLEW "<<glewGetString(GLEW_VERSION)<<endl;
	cout<<"Vendor: "<<glGetString (GL_VENDOR)<<endl;
	cout<<"Renderer: "<<glGetString (GL_RENDERER)<<endl;
	cout<<"Version: "<<glGetString (GL_VERSION)<<endl;
	cout<<"GLSL: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<endl;
}

int main(int argc, char **argv)
{
	atexit(OnShutdown);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);

    glutCreateWindow( "Maze" );
	checkGlew();
    init();
    glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	//glutIdleFunc(some idle func);       
	//gluttimerHunc(some timer func);
	glutMouseFunc(mouse);
    glutKeyboardFunc(key);
    glutMainLoop();

    return 0;
}
