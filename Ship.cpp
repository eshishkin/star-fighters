#include "Ship.h"

SpaceShip::SpaceShip(){};

void SpaceShip::MoveUp()
{
	rcRect.OffsetRect( cos(Phi *PI/180.0) *Speed , sin(Phi*PI/180.0) *Speed );
}

void SpaceShip::AddSpeed(float Sp)
{
	Speed+=Sp;
	
	if(Speed>MAX) Speed=MAX;
	if(Speed < -MAX) Speed=-MAX;
}

void SpaceShip::Init(float x, float y, int width, int height)
{
	CanFire=true;
	bDie=false;
	iType=TYPE_SHIP;
	Phi=0.0f;
	Speed=EPS;

	MYPOINT A(x,y),B(x,y+height),C(x+width,y+height),D(x+width,y);
	rcRect.SetCoord(A,B,C,D);
}

void SpaceShip::TurnLeft(float Phi_)
{
	if(Speed != 0)
	{	
		rcRect.Rotate(-Phi_,rcRect.GetCentre());
		Phi+=Phi_;
	}
}

void SpaceShip::TurnRight(float Phi_)
{
	if(Speed != 0)
	{
		rcRect.Rotate(Phi_,rcRect.GetCentre());
		Phi-=Phi_;
	}
}

void SpaceShip::Fire(LaserWeapon *Laser)
{
	if ( (CanFire==true) && (bDie==false) )
	{
		Laser->Init(rcRect.GetCentre().x , rcRect.GetCentre().y ,70 ,2,Phi);
		Laser->visible=true;
		Laser->SetSpeed(LASER_SPEED);
		CanFire=false;
	}
}

void SpaceShip::Blit(TextureImage Textures)
{
	glBindTexture(GL_TEXTURE_2D, Textures.texID);
	glBegin(GL_QUADS);
		
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(rcRect.GetLeftDown().x , rcRect.GetLeftDown().y);
		
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(rcRect.GetLeftUp().x , rcRect.GetLeftUp().y);
		
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(rcRect.GetRightUp().x , rcRect.GetRightUp().y);
		
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(rcRect.GetRightDown().x , rcRect.GetRightDown().y);

	glEnd();
}