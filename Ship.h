#ifndef SHIP_H
#define SHIP_H

#include "Object.h"
#include "Laser.h"

#define MAX 5
#define EPS 0.0

class SpaceShip:public Object
{
	private:
		float Phi;
		bool CanFire;
		float Speed;
	public:
		SpaceShip();
		void SetPhi(float Phi_) {Phi=Phi_;}
		float GetPhi() { return Phi;}
		void MoveUp();
		void AddSpeed(float Sp);
		void Blit(TextureImage Textures);
		void Init(float x, float y, int width, int height);
		void TurnLeft(float Phi_);
		void TurnRight(float Phi_);
		void Reload() {CanFire=true;}
		void Fire(LaserWeapon* Laser);
};

#endif