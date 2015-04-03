#ifndef MOUSE_H
#define MOUSE_H

#include "vec.h"

class Mouse
{
private:
	bool positionSet;
public:
	vec2 position;
	vec2 deltaPos;

	Mouse()
	{
		positionSet = false;
		deltaPos = vec2(0,0);
		position = vec2(0,0);
	}

	void updatePosition(int x, int y, int w , int h)
	{
		if(x < 200)
		{ 
			x = w - 200; 
			glutWarpPointer(x,y); 
			positionSet = false;
		}
		else if(x > w - 200)
		{ 
			x = 200; 
			glutWarpPointer(x,y); 
			positionSet = false;
		}
		
		if(y < 200)
		{ 
			y = w - 200; 
			glutWarpPointer(x,y);
			positionSet = false;
		}
		else if(y > w - 200)
		{ 
			y = 200; 
			glutWarpPointer(x,y);
			positionSet = false;
		}
		
		if(positionSet)
		{
			deltaPos.x = x - position.x;
			deltaPos.y = y - position.y;

			if(abs(deltaPos.x) < 2) deltaPos.x = 0;
			if(abs(deltaPos.y) < 2) deltaPos.y = 0;
		}
		
		position.x = x;
		position.y = y;
		positionSet = true;
	}
};

#endif