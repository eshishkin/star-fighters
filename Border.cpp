#include "Border.h"

Border::Border()
{
}

void Border::Init(int x, int y, int width, int height)
{
	iType=TYPE_BORDER;

	MYPOINT A(x,y),B(x,y+height),C(x+width,y+height),D(x+width,y);
	rcRect.SetCoord(A,B,C,D);
}


void Border::Blit()
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