#include "Rectangle.h"

MYRECT::MYRECT()
{
	MYPOINT ptTemp(0,0);
	LeftDown=ptTemp;
	LeftUp=ptTemp;
	RightUp=ptTemp;
	RightDown=ptTemp;
	Centre=ptTemp;
};

void MYRECT::operator =(MYRECT A)
{
	LeftDown=A.GetLeftDown();
	LeftUp=A.GetLeftUp();
	RightUp=A.GetRightUp();
	RightDown=A.GetRightDown();
	Centre=A.GetCentre();
};

void MYRECT::SetCoord(MYPOINT LeftDown_, MYPOINT LeftUp_, MYPOINT RightUp_, MYPOINT RightDown_)
{
	LeftDown=LeftDown_;
	LeftUp=LeftUp_;
	RightUp=RightUp_;
	RightDown=RightDown_;
	Centre.x =( RightUp.GetX() - LeftUp.GetX() )*0.5 + LeftUp.GetX() ;
	Centre.y =( RightUp.GetY() - RightDown.GetY() )*0.5 + RightDown.GetY();
};

bool MYRECT::OffsetRect(float dx, float dy)
{
	MYPOINT ptTemp(dx,dy);
	LeftDown+=ptTemp;
	LeftUp+=ptTemp;
	RightUp+=ptTemp;
	RightDown+=ptTemp;
	Centre+=ptTemp;
	
	return true;
};

void MYRECT::Rotate(float Phi,MYPOINT X)
{
	MYPOINT Temp;
	Temp=X;
	this->OffsetRect(-Temp.GetX() ,-Temp.GetY() );
	
	LeftDown=LeftDown.Rotate(Phi);
	LeftUp=LeftUp.Rotate(Phi);
	RightUp=RightUp.Rotate(Phi);
	RightDown=RightDown.Rotate(Phi);
		
	this->OffsetRect(Temp.GetX() ,Temp.GetY() );

}

bool MYRECT::InRect(MYPOINT &A)
{
	MYPOINT Z(A.x+640,A.y);
	int count=0;
	Line Left(LeftDown,LeftUp),Top(LeftUp,RightUp),Right(RightUp,RightDown),Down(RightDown,LeftDown);
	Line Sec(A,Z);  //Secant
	
	if( Sec.IsCrosses(Left) ) count++;
	if( Sec.IsCrosses(Top) ) count++;
	if( Sec.IsCrosses(Right) ) count++;
	if( Sec.IsCrosses(Down) ) count++;

	if(count%2==0)
		return false;
	else
		return true;
}
bool MYRECT::IntersectRect(MYRECT &A)
{
	bool isIntersect=false;
	int i=0;
	
	Line Left(LeftDown,LeftUp),Top(LeftUp,RightUp),Right(RightUp,RightDown),Down(RightDown,LeftDown);
	
	Line ALeft(A.GetLeftDown() ,A.GetLeftUp() ),ATop(A.GetLeftUp() ,A.GetRightUp());
	Line ARight(A.GetRightUp() ,A.GetRightDown() ),ADown(A.GetRightDown() ,A.GetLeftDown() );
	
	if( (Left.IsCrosses(ALeft)) || (Left.IsCrosses(ARight)) || (Left.IsCrosses(ADown)) || (Left.IsCrosses(ATop)) ||
		(Right.IsCrosses(ALeft)) || (Right.IsCrosses(ARight)) || (Right.IsCrosses(ADown)) || (Right.IsCrosses(ATop)) ||
		(Top.IsCrosses(ALeft)) || (Top.IsCrosses(ARight)) || (Top.IsCrosses(ADown)) || (Top.IsCrosses(ATop)) ||
		(Down.IsCrosses(ALeft)) || (Down.IsCrosses(ARight)) || (Down.IsCrosses(ADown)) || (Down.IsCrosses(ATop))
	  )
	
			isIntersect=true;
		else
			isIntersect=false;
	return isIntersect;
}
