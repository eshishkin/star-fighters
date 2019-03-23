#include "Point.h"

MYPOINT::MYPOINT()
{
	x=0;
	y=0;
}

MYPOINT::MYPOINT(float x_, float y_)
{
	x=x_;
	y=y_;
}

MYPOINT MYPOINT::Rotate(float a) 
{
	MYPOINT r;

	a = a * (PI/180.0);
	r.x = (this->x*cos(a)) + (this->y*sin(a));
	r.y = (this->x*-sin(a)) + (this->y*cos(a));

	return r;
}

void MYPOINT::operator =(MYPOINT A)
{
	x=A.GetX();
	y=A.GetY();
}
void MYPOINT::operator +=(MYPOINT A)
{
	x=x+A.GetX();
	y=y+A.GetY();
}

MYPOINT MYPOINT::operator +(MYPOINT A)
{
	MYPOINT B;
	B.x=x+A.GetX();
	B.y=y+A.GetY();

	return B;
}

MYPOINT MYPOINT::operator -(MYPOINT A)
{
	MYPOINT B;
	B.x=x-A.GetX();
	B.y=y-A.GetY();

	return B;
}