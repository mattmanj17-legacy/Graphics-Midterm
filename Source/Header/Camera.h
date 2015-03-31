#ifndef CAMERA_H
#define CAMERA_H

#include "mat.h"

class Camera
{
private:
	Camera(Camera const&);
	void operator=(Camera const&);
	Camera(){}
public:
	static Camera* GetInstance()
	{
		static Camera instance;
		
		return &instance;
	}

	mat4 projection;
	mat4 transformMatrix;

	mat4 GetCameraMatrix()
	{
		return projection * transformMatrix;
	}
};

#endif