#ifndef CAMERA_H
#define CAMERA_H

#include "mat.h"

class Camera
{
private:
	static Camera* instance;

	Camera(){}
public:
	static Camera* GetInstance()
	{
		static bool instanceSet = false;

		if(instanceSet == false)
		{
			instance = new Camera();
			instanceSet = true;
		}
		
		return instance;
	}

	mat4 projection;
	mat4 transformMatrix;

	mat4 GetCameraMatrix()
	{
		projection * transformMatrix;
	}
};

#endif