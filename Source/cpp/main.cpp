#include <iostream>
#include <cmath>
#include <iomanip>
#include <cassert>
#include <vector>
using namespace std;

#include "Angel.h";
#include <GL/glew.h> // for OpenGL extensions
#include <GL/glut.h> // for Glut utility kit
#include "texture.h" // for the bitmap texture loader

// Global Projection Matrices
mat4 projection, modelview;  

#include "GraphicsObject.h"
#include "TexturedQuad.h"

GLfloat  zoom = 1.0;         // Translation factor

GLfloat  fovy = 60.0;		 // Field-of-view in Y direction angle (in degrees)
GLfloat  aspect = 1.0;       // Viewport aspect ratio
GLfloat  zNear = 0.5, zFar = 1000.0;

void display( void )
{
	static float angle = 0.0;

	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );  /*clear the window */

	projection = Perspective( fovy, aspect, zNear, zFar ) * Translate( 0.0, 0.0, -zoom);

	point4  eye( 0.0, 0.0, 0.0, 1.0 );
	point4  at( 0.0, 0.0, -1.0, 1.0 );
	vec4    up( 0.0, 1.0, 0.0, 0.0 );

	modelview = LookAt( eye, at, up ) ;

	// tell the skybox to draw it's vertex
	//go_skybox.draw( theta );

	//// tell the bricks to draw themselves and rotate too!
	//go_brick_1.draw( theta, vec3(0.0,0.0,0.0) );
 //  	go_brick_2.draw( theta, vec3(1.0,0.0,0.0) );
	//go_zebra_2.draw( theta, vec3(1.0,0.0,0.0) );

	//angle += 0.5;
	//if( angle > 360.0 ) angle -= 360.0;

	//go_tree_1.draw( vec3(0.0,angle,0.0), vec3(-1.0,0.0,0.0) );

	// swap the buffers
	glutSwapBuffers();
}


//void spinCube()
//{	
//	if ( axis > -1 )
//	{
//		theta[axis] += 0.5 * dir;
//		if( theta[axis] > 360.0 ) theta[axis] -= 360.0;
//		glutPostRedisplay();
//	}
//}

void mouse(int btn, int state, int x, int y)
{	
	/*if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN)	axis = 1;
	if(btn==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 0;
	if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;*/
	glutPostRedisplay();
}

void mouse_move( int x, int y )
{
	zoom = ( 10.0 / 500.0 ) * y +2.0;  // compute zoom factor 
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
	aspect =  GLfloat (w) / h;
}

void key(unsigned char k, int x, int y)
{
	//if(k == '1') glutIdleFunc(spinCube);
	//if(k == 'r') dir = dir * -1.0;
	//if(k == '2') { glutIdleFunc(NULL); axis = -1; }
    if(k == 'q') exit(0);
}

void init_gl()
{
	glEnable(GL_DEPTH_TEST);


}

void init()
{   
	init_gl();			    // Setup general OpenGL stuff of the object

	//go_skybox.init_data();	        // Setup the data for the this object
	//go_skybox.init_VAO();           // Initialize the vertex array object for this object
	//go_skybox.init_VBO();			// Initialize the data buffers for this object
	//go_skybox.init_shader();		// Initialize the shader objects and textures for skybox
	//go_skybox.init_texture_map();	// Initialize the texture map for this object
	//
	//go_brick_1.init_data();	        // Setup the data for the skybox object
	//go_brick_1.init_VAO();          // Initialize the vertex array object for this object
	//go_brick_1.init_VBO();			// Initialize the data buffers for this object
	//go_brick_1.init_shader();		// Initialize the shader objects and textures for skybox
	//go_brick_1.init_texture_map();	// Initialize the texture map for this object

	//go_brick_2.init_data();	        // Setup the data for the skybox object
	//go_brick_2.init_VAO();          // Initialize the vertex array object for this object
	//go_brick_2.init_VBO();			// Initialize the data buffers for this object
	//go_brick_2.init_shader();		// Initialize the shader objects and textures for skybox
	//go_brick_2.init_texture_map();	// Initialize the texture map for this object
	//
	//go_tree_1.init_data();	    // Setup the data for the skybox object
	//go_tree_1.init_VAO();        // Initialize the vertex array object for this object
	//go_tree_1.init_VBO();		// Initialize the data buffers for this object
	//go_tree_1.init_shader();		// Initialize the shader objects and textures for skybox
	//go_tree_1.init_texture_map();// Initialize the texture map for this object

	//go_zebra_2.init_data();	        // Setup the data for the skybox object
	//go_zebra_2.init_VAO();          // Initialize the vertex array object for this object
	//go_zebra_2.init_VBO();			// Initialize the data buffers for this object
	//go_zebra_2.init_shader();		// Initialize the shader objects and textures for skybox
	//go_zebra_2.init_texture_map();	// Initialize the texture map for this object


	GL_CHECK_ERRORS
}

void OnShutdown()
{
	//go_skybox.cleanup(); // release the textures on the graphics card
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
    // glutInitContextVersion( 3, 2 );
    // glutInitContextProfile( GLUT_CORE_PROFILE );

    glutCreateWindow( "Maze" );
	checkGlew();
    init();
    glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	//glutIdleFunc(spinCube);       // set in key press
	glutMouseFunc(mouse);
	glutMotionFunc(mouse_move);   // Called when mouse moves with a mouse button pressed
    glutKeyboardFunc(key);
    glutMainLoop();

    return 0;
}
