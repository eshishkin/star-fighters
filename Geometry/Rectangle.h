#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <windows.h>
#include <math.h>
#include "Point.h"
#include "Line.h"

class MYRECT
{
	private:
		MYPOINT LeftDown,LeftUp,RightUp,RightDown;
		MYPOINT Centre;
	public:
		MYRECT();
		void operator =(MYRECT A);
		
		MYPOINT GetLeftDown() {return LeftDown; }
		MYPOINT GetLeftUp() {return LeftUp; }
		MYPOINT GetRightUp() {return RightUp; }
		MYPOINT GetRightDown() {return RightDown; }
		MYPOINT GetCentre() {return Centre; }
		
		void SetCoord(MYPOINT LeftDown_, MYPOINT LeftUp_, MYPOINT RightUp_, MYPOINT RightDown_);
		bool OffsetRect(float dx,float dy);
		bool InRect(MYPOINT &A);
		void Rotate(float Phi,MYPOINT X);
		bool IntersectRect(MYRECT &A);
};
#endif