#ifndef CAMERA_H
#define CAMERA_H

#include "mat.h"
#include "Transform.h"

class Camera
{
private:
	// delete other constructors to prevent singleton construction
	Camera(Camera const&);
	void operator=(Camera const&);
	
	Camera()
	{
		fovy = 45.0;
		aspect = 1.0;
		zNear = 0.1;
		zFar = 1000.0;
	}

	// convert camera transform into viewing matrix
	mat4 transformMatrix()
	{
		vec4 eye = transform.position;
		vec4 at =  eye + transform.rotation * -vForward;
		vec4 up = transform.rotation * vUp;
		
		return LookAt(eye,at,up);
	}

public:
	//return singleton instance
	static Camera* GetInstance()
	{
		static Camera instance;
		
		return &instance;
	}

	Transform transform;
	GLfloat  fovy;
	GLfloat  aspect;
	GLfloat  zNear, zFar;

	// return product of perspective matrix and transform matrix
	mat4 GetCameraMatrix()
	{
		return Perspective( fovy, aspect, zNear, zFar ) * transformMatrix();
	}
};

#endif