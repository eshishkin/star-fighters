#ifndef MYPOINT_H
#define MYPOINT_H
#include <math.h>
#define PI 3.1415926535898

class MYPOINT
{
	private:
		//float x,y;
	public:
		float x,y;
		MYPOINT();
		MYPOINT(float x_,float y_);
		MYPOINT Rotate(float a);
		float GetX() { return x; }
		float GetY() { return y; }
		void operator =(MYPOINT A);
		void operator +=(MYPOINT A);
		MYPOINT operator +(MYPOINT A);
		MYPOINT operator -(MYPOINT A);
};
#endif