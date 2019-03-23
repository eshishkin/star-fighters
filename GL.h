#ifndef OPEN_GL
#define OPEN_GL

#include "stdafx.h"
#include "Texture.h"
class OpenGL
{
	GLuint  base;      // база списка отображения для фонта
	public:
		OpenGL();
		void SetPFD(PIXELFORMATDESCRIPTOR &pfd_);
		void InitGL(HDC &hDC_,HGLRC &hRC_,PIXELFORMATDESCRIPTOR &pfd);
		void InitGLScene(GLsizei Width, GLsizei Height);
		void ReSizeGLScene(GLsizei Width, GLsizei Height);
		void DrawText(float x,float y,const char *fmt, ...);
		void LoadGLTextures(GLuint texture[3]);
		//void LoadGLTextures(MyTexture &texture);
		void ReleaseGL(HWND &hWnd,HDC &hDC_,HGLRC &hRC_);
};
#endif