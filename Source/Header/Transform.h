#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "mat.h"
#include "vec.h"
#include "Angel.h"

#define ROTATE_LOCAL true
#define ROTATE_GLOBAL false

class Transform
{	
public:
	mat4 rotation;
	vec3 position;
	vec3 scale;

	Transform()
	{
		scale = vec3(1,1,1);
	}
	
	mat4 getTransformMatrix()
	{
		return rotation * Scale(scale) * Translate(position);
	};

	void rotateX(float angle, bool relativeTo)
	{
		mat4 rot = RotateX(angle);
		
		if(relativeTo == ROTATE_GLOBAL)
		{
			rotation = rotation * rot;
		}
		else if(relativeTo == ROTATE_LOCAL)
		{
			rotation = rot * rotation;
		}
	}

	void rotateY(float angle, bool relativeTo)
	{
		mat4 rot = RotateY(angle);
		
		if(relativeTo == ROTATE_GLOBAL)
		{
			rotation = rotation * rot;
		}
		else if(relativeTo == ROTATE_LOCAL)
		{
			rotation = rot * rotation;
		}
	}

	void rotateZ(float angle, bool relativeTo)
	{
		mat4 rot = RotateY(angle);
		
		if(relativeTo == ROTATE_GLOBAL)
		{
			rotation = rotation * rot;
		}
		else if(relativeTo == ROTATE_LOCAL)
		{
			rotation = rot * rotation;
		}
	}
};

#endif