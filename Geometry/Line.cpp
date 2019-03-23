#include "Line.h"

Line::Line(MYPOINT A_, MYPOINT B_)
{
	A=A_;
	B=B_;
};

bool Line::IsCrosses(Line lnA)
{

   float v1=(lnA.B.x-lnA.A.x)*(A.y-lnA.A.y)-(lnA.B.y-lnA.A.y)*(A.x-lnA.A.x);
   float v2=(lnA.B.x-lnA.A.x)*(B.y-lnA.A.y)-(lnA.B.y-lnA.A.y)*(B.x-lnA.A.x);
   float v3=(B.x-A.x)*(lnA.A.y-A.y)-(B.y-A.y)*(lnA.A.x-A.x);
   float v4=(B.x-A.x)*(lnA.B.y-A.y)-(B.y-A.y)*(lnA.B.x-A.x);
   bool cond=((v1*v2<0) && (v3*v4<0));
   return cond;
};