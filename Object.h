#ifndef OBJECT
#define OBJECT


#include "stdafx.h"
#include "Geometry\Rectangle.h"
#include "Texture.h"

#define TYPE_SHIP 1
#define TYPE_LASER 2
#define TYPE_BORDER 3

#define LASER_SPEED 5
#define ROTATE_SPEED 1


class Object
{
	protected:
		bool bDie;
		int iType;
		//MYRECT rcRect;
	public:
		MYRECT rcRect;
		Object();
		virtual void Init(float x, float y, int width, int height) {}
		void Kill() { bDie=true; }
		bool IsDie() { return bDie; }
		int GetType()  { return iType; }
		MYRECT GetCoord() { return rcRect; }
		virtual bool Collision(Object *something);
};

#endif