#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "mat.h"
#include "vec.h"
#include "Angel.h"

#define ROTATE_LOCAL true
#define ROTATE_GLOBAL false

#define vUp vec4(0,1,0,0);
#define vRight vec4(1,0,0,0);
#define vForward vec4(0,0,1,0);

class Transform
{	
public:
	mat4 rotation;
	vec4 position;
	vec3 scale;

	Transform()
	{
		scale = vec3(1,1,1);
		position = vec4(0,0,0,1);
	}
	
	mat4 getTransformMatrix()
	{
		return Translate(position)  * rotation * Scale(scale);
	};

	void rotateX(float angle, bool relativeTo)
	{
		mat4 rot = RotateX(angle);
		
		if(relativeTo == ROTATE_LOCAL)
		{
			rotation = rotation * rot;
		}
		else if(relativeTo == ROTATE_GLOBAL)
		{
			rotation = rot * rotation;
		}
	}

	void rotateY(float angle, bool relativeTo)
	{
		mat4 rot = RotateY(angle);
		
		if(relativeTo == ROTATE_LOCAL)
		{
			rotation = rotation * rot;
		}
		else if(relativeTo == ROTATE_GLOBAL)
		{
			rotation = rot * rotation;
		}
	}

	void rotateZ(float angle, bool relativeTo)
	{
		mat4 rot = RotateZ(angle);
		
		if(relativeTo == ROTATE_LOCAL)
		{
			rotation = rotation * rot;
		}
		else if(relativeTo == ROTATE_GLOBAL)
		{
			rotation = rot * rotation;
		}
	}

	vec4 forward()
	{
		return rotation * vForward;
	}

	vec4 up()
	{
		return rotation * vUp;
	}

	vec4 right()
	{
		return rotation * vRight;
	}
};

#endif