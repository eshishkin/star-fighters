#ifndef BORDER_H
#define BORDER_H

#include "Object.h"

class Border:public Object
{
	private:
	public:
		Border();
		void Init(int x, int y, int width, int height);
		Border(int x, int y, int width, int height);
		void Blit();
};
#endif