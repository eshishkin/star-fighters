#include "Laser.h"

LaserWeapon::LaserWeapon()
{
}

void LaserWeapon::Move()
{
	rcRect.OffsetRect( cos(Phi *PI/180.0) * LASER_SPEED , sin(Phi*PI/180.0) * LASER_SPEED );
}

void LaserWeapon::Init(float x, float y, int width, int height,float Phi_)
{
	Phi=Phi_;
	iType=TYPE_LASER;
	bDie=false;
	visible=false;

	MYPOINT A(x,y),B(x,y+height),C(x+width,y+height),D(x+width,y);
	MYPOINT Temp(x,y);
	rcRect.SetCoord(A,B,C,D);
	rcRect.Rotate(-Phi,Temp);
}

void LaserWeapon::Blit()
{
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
		glVertex2f(rcRect.GetLeftDown().x , rcRect.GetLeftDown().y);
		glVertex2f(rcRect.GetLeftUp().x , rcRect.GetLeftUp().y);
		glVertex2f(rcRect.GetRightUp().x , rcRect.GetRightUp().y);
		glVertex2f(rcRect.GetRightDown().x , rcRect.GetRightDown().y);
	glEnd();
	glEnable(GL_TEXTURE_2D);
}