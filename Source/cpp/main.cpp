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
#include "Timer.h"
#include "Mouse.h"

typedef vec4 point4;

VertexArrayObject* myVAO;
TriMesh* quadMesh;
Shader* quadShader;
Texture2D* brickTexture;
Timer* gameclock;
Mouse* gameMouse;

int windowWidth = 500;
int windowHeight = 500;

void display( void )
{
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	myVAO->draw();

	glutSwapBuffers();
}

void idle()
{
	gameclock->Update();

	float mouseDragX = gameMouse->deltaPos.x/10;
	float mouseDragY = gameMouse->deltaPos.y/10;
	
	Camera::GetInstance()->transform.rotateY(-90*gameclock->deltaTime*mouseDragX,ROTATE_GLOBAL);
	Camera::GetInstance()->transform.rotateX(-180*gameclock->deltaTime*mouseDragY,ROTATE_LOCAL);

	glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)
{	
}

void mouseMove(int x, int y)
{
	gameMouse->updatePosition(x, y, windowWidth, windowHeight);
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
	Camera::GetInstance()->aspect = GLfloat (w) / h;
	windowWidth = w;
	windowHeight = h;
}

void key(unsigned char k, int x, int y)
{
	if(k == 'q') exit(0);
}

void init_gl()
{
	glEnable(GL_DEPTH_TEST);
}

void makeUnitTexturedQuad(TriMesh* mesh)
{
	vec4 a(-0.5, 0.5, 0.0, 1.0);	vec4 b(0.5, 0.5, 0.0, 1.0); 
	 
	vec4 d(-0.5,-0.5, 0.0, 1.0);	vec4 c(0.5,-0.5, 0.0, 1.0);
	
	mesh->addPoint(a, vec2(0,1));
	mesh->addPoint(c, vec2(1,0));
	mesh->addPoint(b, vec2(1,1));
	
	mesh->addPoint(d, vec2(0,0));
	mesh->addPoint(c, vec2(1,0));
	mesh->addPoint(a, vec2(0,1));
}

void init()
{   
	init_gl();

	gameclock = new Timer();
	gameMouse = new Mouse();

	quadShader = new Shader("glsl/quad_vshader.glsl","glsl/quad_fshader.glsl");
	brickTexture = new Texture2D("Brick.bmp");
	quadMesh = new TriMesh();
	makeUnitTexturedQuad(quadMesh);

	myVAO = new VertexArrayObject(quadMesh, brickTexture, quadShader);
	
	myVAO->transform.position.z = -0.5;

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

//void setMouse(int _)
//{
//	glutWarpPointer(250,250);
//	glutTimerFunc(100, setMouse, 0);
//}

int main(int argc, char **argv)
{
	atexit(OnShutdown);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);

    glutCreateWindow( "Maze" );
	checkGlew();
    init();
    glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(mouseMove);
	//glutTimerFunc(100, setMouse, 0);
    glutKeyboardFunc(key);
	glutWarpPointer(windowWidth/2,windowHeight/2);
	glutSetCursor(GLUT_CURSOR_NONE);
    glutMainLoop();

    return 0;
}
