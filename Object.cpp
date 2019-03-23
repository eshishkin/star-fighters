#include "Object.h"

Object::Object()
{
}

bool Object::Collision(Object *something)
{	
	if( rcRect.IntersectRect(something->rcRect)== false)
		return false;
	else 
		return true;
}
