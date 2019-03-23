#ifndef GAME_H
#define GAME_H

#include "stdafx.h"
#include "Object.h"
#include "Ship.h"
#include "Border.h"
#include "Laser.h"

#define SHIP_RED 0
#define SHIP_BLUE 1
#define LASER_RED 0
#define LASER_BLUE 1

#define SHIP_SIZE 75
#define MAX_SCORE 5

class CGame
{
	private:
		bool keys[256];
		SpaceShip* Ships[2];
		LaserWeapon* Lasers[2];
		Border* Borders[4];
		int score[2];
		int Winner;
		int Width;
		int Height;
	public:
		CGame(int Width_,int Height_);
		~CGame();
		void Init();
		int GetScore(int n) { return score[n]; }
		int GetWinner() { return Winner; }
		void SetSize(int Width_,int Height_);
		void GetKeys(bool Keys_[256]);
		void CollisionAnalys();
		void SetFrame();
		void Blit(int Width_,int Height_,TextureImage Textures[2] );
		bool bEnd;
};
#endif