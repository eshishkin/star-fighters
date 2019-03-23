#include "GL.h"

OpenGL::OpenGL()
{
};
void OpenGL::SetPFD(PIXELFORMATDESCRIPTOR &pfd_)
{
	PIXELFORMATDESCRIPTOR pfd=
	{
		sizeof(PIXELFORMATDESCRIPTOR),	// ������ ���� ���������
		1,				// ����� ������ (?)
		PFD_DRAW_TO_WINDOW |// ������ ��� ����
		PFD_SUPPORT_OPENGL |// ������ ��� OpenGL
		PFD_DOUBLEBUFFER,// ������ ��� �������� ������
		PFD_TYPE_RGBA,	// ��������� RGBA ������
		16,				// ����� 16 ��� ������� �����
		0, 0, 0, 0, 0, 0,// ������������� �������� ����� (?)
		0,				// ��� ������ ������������
		0,				// ��������� ��� ������������ (?)
		0,				// ��� ������ �����������
		0, 0, 0, 0,		// ���� ����������� ������������ (?)
		16,				// 16 ������ Z-����� (����� �������)  
		0,				// ��� ������ ����������
		0,				// ��� ��������������� ������� (?)
		PFD_MAIN_PLANE,	// ������� ���� ���������
		0,				// ������ (?)
		0, 0, 0			// ����� ���� ������������ (?)
	};
	pfd_=pfd;
}
void OpenGL::InitGL(HDC &hDC_, HGLRC &hRC_,PIXELFORMATDESCRIPTOR &pfd)
{
	GLuint	PixelFormat;
	PixelFormat = ChoosePixelFormat(hDC_, &pfd);
	SetPixelFormat(hDC_,PixelFormat,&pfd);
	hRC_ = wglCreateContext(hDC_);
	wglMakeCurrent(hDC_, hRC_);
	
	HFONT  font;            // ������������� �����

	  base = glGenLists(96);  // ������� ����� ��� 96 �������� ( ����� )

	  font = CreateFont(  -24,        // ������ ����� 
		    0,        // ������ �����
			0,        // ���� ���������
			0,        // ���� �������
			FW_BOLD,      // ������ ������
			FALSE,        // ������
			FALSE,        // �������������
			FALSE,        // ��������������
			ANSI_CHARSET,      // ������������� ������ ��������
			OUT_TT_PRECIS,      // �������� ������
			CLIP_DEFAULT_PRECIS,    // �������� ���������
			ANTIALIASED_QUALITY,    // �������� ������
			FF_DONTCARE|DEFAULT_PITCH,  // ��������� � ���
			"Courier New");      // ��� ������
	SelectObject(hDC_, font);        // ������� �����, ��������� ����
	wglUseFontBitmaps(hDC_, 32, 96, base); // ��������� 96 �������� ������� � �������
}

void OpenGL::InitGLScene(GLsizei Width, GLsizei Height)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
							// ������� ������ � ������ ����
	glClearDepth(1.0);		// ��������� ������� ������ �������
	glDepthFunc(GL_LESS);	// ��� ����� �������
	glEnable(GL_DEPTH_TEST);// ��������� ���� �������
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);// ��������� ������� �������� �����������
	glMatrixMode(GL_PROJECTION);// ����� ������� ��������
	glLoadIdentity();		// ����� ������� ��������
	gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
							// ��������� ����������� �������������� �������� ��� ����
	glMatrixMode(GL_MODELVIEW);// ����� ������� ��������� ������
}

void OpenGL::DrawText(float x,float y,const char *fmt, ...)        // �������� ������� "������" GL
{
  char    text[256];      // ����� ��� ����� ������
  va_list    ap;          // ��������� �� ������ ����������
  if (fmt == NULL)     // ���� ��� ������
    return;            // ������ �� ������
	
  va_start(ap, fmt);           // ������ ������ ����������
      vsprintf(text, fmt, ap); // � ��������������� �������� � �������� ����
  va_end(ap);                  // ��������� ���������� � ������

  glDisable(GL_TEXTURE_2D);

  glLoadIdentity();
  glRasterPos2f(x,y);
  glPushAttrib(GL_LIST_BIT);      // ����������� ���� ������ ����������� ( ����� )
  glListBase(base - 32);          // ������ ���� ������� � 32 ( ����� )
  glCallLists(strlen(text), GL_UNSIGNED_BYTE, text); // ����� �������� ����������� ( ����� )
  glPopAttrib(); // ������� ����� ������ ����������� ( ����� )
  glEnable(GL_TEXTURE_2D);

}

void OpenGL::ReSizeGLScene(GLsizei Width, GLsizei Height)
{
	if (Height==0)		// �������������� ������� �� ����, ���� ���� ������� ����
		Height=1;

	glViewport(0, 0, Width, Height);
		// ����� ������� ������� ������ � ������������� ��������������

	glMatrixMode(GL_PROJECTION);// ����� ������� ��������
	glLoadIdentity();			// ����� ������� ��������

	gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
		// ���������� ����������� �������������� �������� ��� ����
	glMatrixMode(GL_MODELVIEW);	// ����� ������� ��������� ������
}
/*
void OpenGL::LoadGLTextures(GLuint texture[3])
{
	// �������� ��������
	AUX_RGBImageRec* text[2];

	for(int i=0;i<2;i++)
		text[i]=new AUX_RGBImageRec;

	//text=new AUX_RGBImageRec[3];
	text[0] = auxDIBImageLoad("Textures//Ship1.bmp");
	text[1] = auxDIBImageLoad("Textures//Ship2.bmp");
	// �������� ��������
	glGenTextures(0, &texture[0]);
	glGenTextures(1, &texture[1]);

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	
	for(int i=0;i<2;i++)
		glTexImage2D(GL_TEXTURE_2D, 0, 3, text[i]->sizeX, text[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, text[i]->data);

}*/

void OpenGL::ReleaseGL(HWND &hWnd, HDC &hDC_, HGLRC &hRC_)
{
	glDeleteLists(base, 96);
	wglMakeCurrent(hDC_,NULL);
	wglDeleteContext(hRC_);
	ReleaseDC(hWnd,hDC_);
}