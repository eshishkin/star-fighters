#ifndef LASER_H
#define LASER_H

#include "Object.h"

class LaserWeapon:public Object
{
	private:
		float Phi;
		float Speed;
	public:
		bool visible;
		LaserWeapon();
		void SetSpeed(float Sp) {Speed=Sp;}
		void Move();
		void Blit();
		void Init(float x, float y, int width, int height,float Phi_);
};
#endif