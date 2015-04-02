#ifndef CAMERA_H
#define CAMERA_H

#include "mat.h"
#include "Transform.h"

class Camera
{
private:
	Camera(Camera const&);
	void operator=(Camera const&);
	Camera()
	{
		fovy = 45.0;
		aspect = 1.0;
		zNear = 0.1;
		zFar = 1000.0;
	}

	mat4 transformMatrix()
	{
		vec4 eye = transform.position;
		vec4 at =  eye + transform.rotation * -vForward;
		vec4 up = transform.rotation * vUp;
		
		return LookAt(eye,at,up);
	}

public:
	static Camera* GetInstance()
	{
		static Camera instance;
		
		return &instance;
	}

	Transform transform;
	GLfloat  fovy;		 // Field-of-view in Y direction angle (in degrees)
	GLfloat  aspect;       // Viewport aspect ratio
	GLfloat  zNear, zFar;

	mat4 GetCameraMatrix()
	{
		return Perspective( fovy, aspect, zNear, zFar ) * transformMatrix();
	}
};

#endif