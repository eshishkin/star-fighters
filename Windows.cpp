#include "Windows.h"

Window::Window()
{
	Width=0;
	Height=0;
	fullscreen=false;
	ChangeSize=false;
}

bool Window::RegWindow(HINSTANCE hInstance,WNDPROC WndProc)
{
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc		= (WNDPROC) WndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInstance;
	wc.hIcon			= LoadIcon(NULL,"ORION2.ico");
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= NULL;
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= "WinClass";

	RegisterClass(&wc);

	return true;
}

bool Window::Create(HINSTANCE &hInstance,HWND &hWnd,int Width_, int Height_)
{
	Width=Width_;
	Height=Height_;

	hWnd = CreateWindow(
	"WinClass",
	"Star Fighters",	// Заголовок вверху окна
	WS_OVERLAPPEDWINDOW |
	//WS_POPUP |
	WS_CLIPCHILDREN |
	WS_CLIPSIBLINGS,

	0, 0,			// Позиция окна на экране
	Width, Height,		// Ширина и высота окна

	NULL,
	NULL,
	hInstance,
	NULL);

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	SetFocus(hWnd);
	
	
	return true;
}

bool Window::SwitchFullScreen()
{
	DEVMODE dmScreenSettings;			// Режим работы

	memset(&dmScreenSettings, 0, sizeof(DEVMODE));	// Очистка для хранения установок
	dmScreenSettings.dmSize	= sizeof(DEVMODE);		// Размер структуры Devmode
	dmScreenSettings.dmPelsWidth	= 640;			// Ширина экрана
	dmScreenSettings.dmPelsHeight	= 480;			// Высота экрана
	dmScreenSettings.dmFields	= DM_PELSWIDTH | DM_PELSHEIGHT;	// Режим Пиксела
	ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
	return true;
}

void Window::SetSize(int Width_,int Height_)
{
	Width=Width_;
	Height=Height_;
	ChangeSize = true;
}

bool Window::IsSizeChange()
{
	if(ChangeSize)
		return true;
	else 
		return false;
}