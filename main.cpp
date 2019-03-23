#include "stdafx.h"
#include "GL.h"
#include "Texture.h"
#include "Game.h"
#include "Windows.h"

HDC hDC;	
Window *Wnd;
OpenGL *OGL;
float FPS;
void CalculateFrameRate()
{
    static float framesPerSecond = 0.0f;    //наши фпс
    static float lastTime = 0.0f;           //Тут хранится время, прошедшее с последнего кадра
    static char strFrameRate[50] = {0};     //Строка для вывода
    float currentTime = timeGetTime() * 0.001f;
    ++framesPerSecond;

    if(currentTime - lastTime > 1.0f)
    {
		lastTime = currentTime;
        FPS=framesPerSecond;
        framesPerSecond = 0;
    }
}

CTexture *Texture;
TextureImage Textures[2];
bool keys[256];
bool bPause=false;

LRESULT CALLBACK WndProc(
				HWND	hWnd,
				UINT	message,
				WPARAM	wParam,
				LPARAM	lParam)
{
	RECT	Screen;
	PIXELFORMATDESCRIPTOR pfd;
	HGLRC hRC;

	switch (message)	// Тип сообщения
	{
		case WM_CREATE:
			hDC = GetDC(hWnd);	
			OGL = new OpenGL;
			OGL->SetPFD(pfd);
			OGL->InitGL(hDC,hRC,pfd);
			GetClientRect(hWnd, &Screen);
			OGL->InitGLScene(Screen.right, Screen.bottom);
			Texture = new CTexture();
    		Texture->LoadTexture(IL_BMP,"Textures\\Ship1.bmp",&Textures[0]);
			Texture->LoadTexture(IL_BMP,"Textures\\Ship2.bmp",&Textures[1]);	
		break;

		case WM_DESTROY:
		case WM_CLOSE:
			ChangeDisplaySettings(NULL, 0);
			OGL->ReleaseGL(hWnd,hDC,hRC);
			delete OGL;
			delete Texture;
			PostQuitMessage(0);
		break;

		case WM_KEYDOWN:
			keys[wParam] = TRUE;
		break;

		case WM_KEYUP:
			keys[wParam] = FALSE;
		break;

		case WM_SIZE:
			Wnd->SetSize(LOWORD(lParam),HIWORD(lParam));
			OGL->ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));
		break;

		default:
	return (DefWindowProc(hWnd, message, wParam, lParam));
	}
	return (0);
}

int WINAPI WinMain(
		HINSTANCE hInstance,
		HINSTANCE hPrevInstance, 
		LPSTR lpCmdLine,
		int nCmdShow)
{
	MSG		msg;	// Структура сообщения Windows
	HWND		hWnd;// Сохранение дискриптора окна

	Wnd=new Window;
	Wnd->RegWindow(hInstance,WndProc);
	Wnd->Create(hInstance,hWnd,640,480);
	
	CGame* Game;
	Game=new CGame(Wnd->GetWidth() , Wnd->GetHeight() );

	while (1)
	{
		// Обработка всех сообщений
		while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (GetMessage(&msg, NULL, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				return TRUE;
			}
		}
		
		if( Wnd->IsSizeChange() )
			Game->SetSize( Wnd->GetWidth() , Wnd->GetHeight() );
		
		if (keys[VK_ESCAPE]) 
		{
			SendMessage(hWnd,WM_CLOSE,0,0);	
			delete Game;
			delete Wnd;
		}
//		if (keys['H']) Game->About();
		if (keys[VK_PAUSE]) 
		{
			bPause=!bPause;
			if(bPause)
				OGL->DrawText( (Wnd->GetWidth()/2)-20 ,Wnd->GetHeight()-20,"PAUSE");
		}
		
		if( (Game->bEnd==false) && (bPause==false) )
		{
			CalculateFrameRate();
			Game->GetKeys(keys);
			Game->SetFrame();
			Game->CollisionAnalys();
			Game->Blit( Wnd->GetWidth() , Wnd->GetHeight(),Textures);

			OGL->DrawText(Wnd->GetWidth()/2,24,"FPS: %f",FPS );
			OGL->DrawText(10,Wnd->GetHeight()-24,"Red: %i",Game->GetScore(SHIP_RED) );
			OGL->DrawText(Wnd->GetWidth()-110,Wnd->GetHeight()-24,"Blue: %i",Game->GetScore(SHIP_BLUE) );
		}
		
		if(Game->GetWinner()== SHIP_RED)
			OGL->DrawText(Wnd->GetWidth()/2-100 ,Wnd->GetHeight()-20,"Red is a Winner");
		if(Game->GetWinner()==SHIP_BLUE)
			OGL->DrawText(Wnd->GetWidth()/2-110 ,Wnd->GetHeight()-20,"Blue is a Winner");
		
		SwapBuffers(hDC);
	}
}
