#ifndef WIN_H
#define WIN_H

#include "stdafx.h"

class Window
{
	private:
		WNDCLASS wc;
		int Width;
		int Height;
		bool fullscreen;
		bool ChangeSize;
	public:
		Window();
		bool RegWindow(HINSTANCE hInstance,WNDPROC WndProc);
		bool Create(HINSTANCE &hInstance,HWND &hWnd,int Width_,int Height_);
		bool SwitchFullScreen();
		bool IsSizeChange();
		void SetSize(int Width_,int Height_);
		int GetWidth() { return Width; }
		int GetHeight() { return Height; }
};

#endif