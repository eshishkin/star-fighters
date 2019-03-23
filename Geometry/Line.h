#ifndef LINE_H
#define LINE_H

#include "Point.h"

class Line
{
	MYPOINT A,B;
	public:
		Line(MYPOINT A_,MYPOINT B_);
		void operator -(float z);
		bool IsCrosses(Line lnA);
};
#endif