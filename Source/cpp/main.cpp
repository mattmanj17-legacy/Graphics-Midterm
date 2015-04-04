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
#include "SkyBox.h"

VertexArrayObject* wallVAO;
VertexArrayObject* treeVAO;

TriMesh* brickMesh;
TriMesh* treeMesh;

Shader* quadShader;

Texture2D* brickTexture;
Texture2D* treeTexture;

Timer* gameclock;
Mouse* gameMouse;

SkyBox skybox;

vector<Transform> walls;
vector<Transform> trees;

int windowWidth = 500;
int windowHeight = 500;

// wasd key states
bool wDown = false;
bool sDown = false;
bool aDown = false;
bool dDown = false;

void display( void )
{
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// draw all walls
	for(int i = 0; i< walls.size(); i++)
	{
		wallVAO->drawAt(walls[i]);
	}

	// draw all trees
	for(int i = 0; i< trees.size(); i++)
	{
		treeVAO->drawAt(trees[i]);
	}

	// draw the skybox
	skybox.draw();

	glutSwapBuffers();
}

// helper function to make sure a given value is bouded between two numbers
float clamp(float low, float high, float value)
{
	if(value < low) return low;
	if(value > high) return high;
	return value;
}

void idle()
{
	//tick
	gameclock->Update();

	// rotate camera based on mouse movement
	float mouseDragX = gameMouse->deltaPos.x/10;
	float mouseDragY = gameMouse->deltaPos.y/10;
	
	Camera::GetInstance()->transform.rotateY(-90*gameclock->deltaTime*mouseDragX,ROTATE_GLOBAL);
	Camera::GetInstance()->transform.rotateX(-180*gameclock->deltaTime*mouseDragY,ROTATE_LOCAL);

	// go left and right
	if(aDown)
	{
		Camera::GetInstance()->transform.position -= Camera::GetInstance()->transform.right()*gameclock->deltaTime;
	}
	else if(dDown)
	{
		Camera::GetInstance()->transform.position += Camera::GetInstance()->transform.right()*gameclock->deltaTime;
	}

	// go forward and backwaard
	if(wDown)
	{
		vec4 forward = Camera::GetInstance()->transform.forward();
		forward.y = 0;
		forward = normalize(forward);
		Camera::GetInstance()->transform.position -= forward*gameclock->deltaTime*1.5;
	}
	else if(sDown)
	{
		vec4 forward = Camera::GetInstance()->transform.forward();
		forward.y = 0;
		forward = normalize(forward);
		Camera::GetInstance()->transform.position += forward*gameclock->deltaTime*1.5;
	}

	// clamp camera posistion inside the level
	Camera::GetInstance()->transform.position.x = clamp(0, 9, Camera::GetInstance()->transform.position.x);
	Camera::GetInstance()->transform.position.z = clamp(0, 9, Camera::GetInstance()->transform.position.z);

	glutPostRedisplay();
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
	if(k == 'w') wDown = true;
	if(k == 's') sDown = true;
	if(k == 'a') aDown = true;
	if(k == 'd') dDown = true;
	
	if(k == 'q') exit(0);
}

void keyUp(unsigned char k, int x, int y)
{
	if(k == 'w') wDown = false;
	if(k == 's') sDown = false;
	if(k == 'a') aDown = false;
	if(k == 'd') dDown = false;
}

void init_gl()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Prevent alpha values of less than 0.1 from writing out the the depth test buffer.
	glAlphaFunc ( GL_GREATER, 0.1 ) ;
    glEnable ( GL_ALPHA_TEST ) ;
}

void makeBrickMesh(TriMesh* mesh)
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

void makeTreeMesh(TriMesh* mesh)
{
	vec4 a(-0.25, 0.5, 0.0, 1.0);	vec4 b(0.25, 0.5, 0.0, 1.0); 
	 
	vec4 d(-0.25,-0.5, 0.0, 1.0);	vec4 c(0.25,-0.5, 0.0, 1.0);

	mesh->addPoint(a, vec2(0,1));
	mesh->addPoint(c, vec2(0.5,0));
	mesh->addPoint(b, vec2(0.5,1));
	
	mesh->addPoint(d, vec2(0,0));
	mesh->addPoint(c, vec2(0.5,0));
	mesh->addPoint(a, vec2(0,1));

	vec4 a0(0.0, 0.5,-0.25, 1.0);	vec4 b0(0.0, 0.5, 0.25, 1.0); 
	 
	vec4 d0(0.0,-0.5,-0.25, 1.0);	vec4 c0(0.0,-0.5, 0.25, 1.0);

	mesh->addPoint(a0, vec2(0.5,1));
	mesh->addPoint(c0, vec2(1,0));
	mesh->addPoint(b0, vec2(1,1));
	
	mesh->addPoint(d0, vec2(0.5,0));
	mesh->addPoint(c0, vec2(1,0));
	mesh->addPoint(a0, vec2(0.5,1));
}

void init()
{   
	init_gl();

	srand(time(NULL));

	gameclock = new Timer();
	gameMouse = new Mouse();

	//use kent's skybox
	skybox.init_data();
	skybox.init_VAO();
	skybox.init_VBO();
	skybox.init_shader();
	skybox.init_texture_map();

	// load my shader
	quadShader = new Shader("glsl/quad_vshader.glsl","glsl/quad_fshader.glsl");
	
	// load textures
	brickTexture = new Texture2D("Brick.bmp");
	treeTexture = new Texture2D("trees.bmp");

	//generat meshes
	brickMesh = new TriMesh();
	makeBrickMesh(brickMesh);

	treeMesh = new TriMesh();
	makeTreeMesh(treeMesh);

	// creat tree and wall voa's
	treeVAO = new VertexArrayObject(treeMesh, treeTexture, quadShader);
	wallVAO = new VertexArrayObject(brickMesh, brickTexture, quadShader);

	// rotate camera to point into the level
	Camera::GetInstance()->transform.rotateY(-90 - 45,ROTATE_GLOBAL);
	
	//10 random trees
	for(int i = 0; i < 10; i++)
	{
		vec4 pos;
		pos.w = 1;

		float rot = 0;
		
		pos.x = rand()%900;
		pos.x /= 100;

		pos.z = rand()%900;
		pos.z /= 100;

		rot = rand()%9000;
		rot /= 100;

		trees.push_back(Transform());
		trees[trees.size() - 1].position = pos;
		trees[trees.size() - 1].rotateY(rot, ROTATE_GLOBAL);
	}

	//z- wall
	for(int i = 0; i < 10; i++)
	{
		walls.push_back(Transform());
		walls[walls.size() - 1].position.z = -0.5;
		walls[walls.size() - 1].position.x = i; 
	}

	//z+ wall
	for(int i = 0; i < 10; i++)
	{
		walls.push_back(Transform());
		walls[walls.size() - 1].position.z = 9.5;
		walls[walls.size() - 1].position.x = i; 
	}

	//x- wall
	for(int i = 0; i < 10; i++)
	{
		walls.push_back(Transform());
		walls[walls.size() - 1].position.x = -0.5;
		walls[walls.size() - 1].position.z = i;
		walls[walls.size() - 1].rotateY(90,ROTATE_GLOBAL);
	}

	//x+ wall
	for(int i = 0; i < 10; i++)
	{
		walls.push_back(Transform());
		walls[walls.size() - 1].position.x = 9.5;
		walls[walls.size() - 1].position.z = i;
		walls[walls.size() - 1].rotateY(90,ROTATE_GLOBAL);
	}

	//y- floor
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			walls.push_back(Transform());
			walls[walls.size() - 1].position.y = -0.5;
			walls[walls.size() - 1].position.x = i;
			walls[walls.size() - 1].position.z = j;
			walls[walls.size() - 1].rotateX(90,ROTATE_GLOBAL);
		}
	}

	GL_CHECK_ERRORS
}

void OnShutdown()
{
	// deleat everything
	delete wallVAO;
	delete treeVAO;

	delete brickMesh;
	delete treeMesh;

	delete quadShader;

	delete brickTexture;
	delete treeTexture;

	delete gameclock;
	delete gameMouse;
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
    glutInitWindowSize(windowWidth, windowHeight);

    glutCreateWindow( "Maze" );
	checkGlew();
    init();
    glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutPassiveMotionFunc(mouseMove);
    glutKeyboardFunc(key);
	glutKeyboardUpFunc(keyUp);
	glutWarpPointer(windowWidth/2,windowHeight/2);
	glutSetCursor(GLUT_CURSOR_NONE);
    glutMainLoop();

    return 0;
}
