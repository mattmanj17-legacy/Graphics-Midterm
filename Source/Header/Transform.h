#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "mat.h"

class Transform
{
private:
	mat4 rotation;
protected:

public:
	vec3 posision;
	vec3 scale;
	
	mat4 getModelView
};

#endif