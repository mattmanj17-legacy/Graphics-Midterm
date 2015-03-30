#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
	GLfloat  zoom = 1.0;         // Translation factor

	GLfloat  fovy = 60.0;		 // Field-of-view in Y direction angle (in degrees)
	GLfloat  aspect = 1.0;       // Viewport aspect ratio
	GLfloat  zNear = 0.5, zFar = 1000.0;
};

#endif