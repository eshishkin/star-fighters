#include "Game.h"

CGame::CGame(int Width_,int Height_)
{
	Width=Width_;
	Height=Height_;
	bEnd=false;
	Winner=-1;
	for(int i=0;i<4;i++)
		Borders[i]=new Border;
	
	Borders[0]->Init(0,Height-5,Width,5);
	Borders[1]->Init(Width,0,5,Height);
	Borders[2]->Init(0,0,Width,5);
	Borders[3]->Init(0,0,5,Height);
	
	for(int i=0;i<2;i++)
	{
		Ships[i]=new SpaceShip;
		Lasers[i]=new LaserWeapon;
		score[i]=0;
	}

	Ships[SHIP_RED]->Init(20,20, SHIP_SIZE , SHIP_SIZE);
	Ships[SHIP_BLUE]->Init(520,320, SHIP_SIZE , SHIP_SIZE);

}
void CGame::SetSize(int Width_, int Height_)
{
	Width=Width_;
	Height=Height_;
}

void CGame::Init()
{
	srand((unsigned)time(NULL));
	int j=1;
	float x=rand()%(Width-120)+20,y=rand()%(Height-110)+20;
	
	for(int i=0;i<2;i++)
	{	
		if ( Ships[i]->IsDie() ) 
		{
			//float x=rand()%Width-110,y=rand()%Height-110;
			x= rand()%(Width-120)+15;
			y= rand()%(Height-120)+15;

			Ships[i]->Init(x,y, SHIP_SIZE , SHIP_SIZE);
		}
		j--;
	}
}

void CGame::GetKeys(bool Keys_[256])
{
	for(int i=0;i<256;i++)
		keys[i]=Keys_[i];
}

void CGame::CollisionAnalys()
{

	for(int i=0;i<4;i++)
	{
		for(int j=0;j<2;j++)
		{
			if(Ships[j]->Collision(Borders[i]) )
			{
				Ships[j]->SetPhi(Ships[j]->GetPhi()-90);
				Ships[j]->rcRect.Rotate(90, Ships[j]->rcRect.GetCentre() );
			}
			if(Lasers[j]->Collision(Borders[i]) )
			{
				Lasers[j]->visible=false;
				Lasers[j]->SetSpeed(0);
				Ships[j]->Reload();
			}
		}
	}
	
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<2;j++)
		{			
			if( (Lasers[i]->Collision(Ships[j])) && (i!=j) )
			{
				Lasers[i]->visible=false;
				//Lasers[i]->SetSpeed(0);
				Lasers[i]->Init(0,0,1,1,0);
				Ships[i]->Reload();
				
				if( !Ships[j]->IsDie() )
				{
					Ships[j]->Kill();
					score[i]++;
					this->Init();
				}
			}
		}
	}
	

	if(Ships[SHIP_RED]->Collision(Ships[SHIP_BLUE]) )
	{
		Ships[SHIP_RED]->Kill();
		Ships[SHIP_BLUE]->Kill();
		this->Init();
	}
}

void CGame::SetFrame()
{
	if( (score[SHIP_RED]>=MAX_SCORE) && (score[SHIP_RED] > score[SHIP_BLUE] ) )
	{
		Winner=SHIP_RED;
		bEnd=true;
	}
	
	if( (score[SHIP_BLUE]>=MAX_SCORE) && (score[SHIP_RED] < score[SHIP_BLUE] ) )
	{
		Winner=SHIP_BLUE;
		bEnd=true;
	}
	
	Borders[0]->Init(0,Height-5,Width,5);
	Borders[1]->Init(Width-5,0,5,Height);
	Borders[2]->Init(0,0,Width,5);
	Borders[3]->Init(0,0,5,Height);

	Ships[SHIP_RED]->MoveUp();
	Ships[SHIP_BLUE]->MoveUp();
	Lasers[LASER_RED]->Move();
	Lasers[LASER_BLUE]->Move();

	if (keys[VK_UP]) Ships[SHIP_RED]->AddSpeed(0.1f);
	if (keys[VK_DOWN]) Ships[SHIP_RED]->AddSpeed(-0.1f);
	if (keys[VK_LEFT]) Ships[SHIP_RED]->TurnLeft(1);
	if (keys[VK_RIGHT]) Ships[SHIP_RED]->TurnRight(1);
	if (keys[VK_RETURN]) Ships[SHIP_RED]->Fire(Lasers[LASER_RED]);

	if (keys['W']) Ships[SHIP_BLUE]->AddSpeed(0.1f);
	if (keys['S']) Ships[SHIP_BLUE]->AddSpeed(-0.1f);
	if (keys['A']) Ships[SHIP_BLUE]->TurnLeft(1);
	if (keys['D']) Ships[SHIP_BLUE]->TurnRight(1);
	if (keys['F']) Ships[SHIP_BLUE]->Fire(Lasers[LASER_BLUE]);
	
}

void CGame::Blit(int Width_,int Height_,TextureImage Textures[2])
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// очистка Ёкрана и буфера глубины
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	gluOrtho2D( 0, Width_,0, Height_ );
	//glOrtho( 0, Width_,0, Height_ ,0,-5 );
	glMatrixMode( GL_MODELVIEW ); 
	glLoadIdentity();
	
	if( !Ships[SHIP_RED]->IsDie() )
		Ships[SHIP_RED]->Blit(Textures[0]);
	if( !Ships[SHIP_BLUE]->IsDie() )
		Ships[SHIP_BLUE]->Blit(Textures[1]);
		
	if(Lasers[LASER_RED]->visible)
		Lasers[LASER_RED]->Blit();
	if(Lasers[LASER_BLUE]->visible)
		Lasers[LASER_BLUE]->Blit();
	
	for(int i=0;i<4;i++)
		Borders[i]->Blit();
	glFlush();
}

CGame::~CGame()
{
	for(int i=0;i<4;i++)
		delete Borders[i];
	
	for(int i=0;i<2;i++)
		delete Ships[i];
	
	for(int i=0;i<2;i++)
		delete Lasers[i];
}
