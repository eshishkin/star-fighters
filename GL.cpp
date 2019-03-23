#include "GL.h"

OpenGL::OpenGL()
{
};
void OpenGL::SetPFD(PIXELFORMATDESCRIPTOR &pfd_)
{
	PIXELFORMATDESCRIPTOR pfd=
	{
		sizeof(PIXELFORMATDESCRIPTOR),	// Размер этой структуры
		1,				// Номер версии (?)
		PFD_DRAW_TO_WINDOW |// Формат для Окна
		PFD_SUPPORT_OPENGL |// Формат для OpenGL
		PFD_DOUBLEBUFFER,// Формат для двойного буфера
		PFD_TYPE_RGBA,	// Требуется RGBA формат
		16,				// Выбор 16 бит глубины цвета
		0, 0, 0, 0, 0, 0,// Игнорирование цветовых битов (?)
		0,				// нет буфера прозрачности
		0,				// Сдвиговый бит игнорируется (?)
		0,				// Нет буфера аккумуляции
		0, 0, 0, 0,		// Биты аккумуляции игнорируются (?)
		16,				// 16 битный Z-буфер (буфер глубины)  
		0,				// Нет буфера траффарета
		0,				// Нет вспомогательных буферов (?)
		PFD_MAIN_PLANE,	// Главный слой рисования
		0,				// Резерв (?)
		0, 0, 0			// Маски слоя игнорируются (?)
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
	
	HFONT  font;            // Идентификатор фонта

	  base = glGenLists(96);  // Выделим место для 96 символов ( НОВОЕ )

	  font = CreateFont(  -24,        // Высота фонта 
		    0,        // Ширина фонта
			0,        // Угол отношения
			0,        // Угол Наклона
			FW_BOLD,      // Ширина шрифта
			FALSE,        // Курсив
			FALSE,        // Подчеркивание
			FALSE,        // Перечеркивание
			ANSI_CHARSET,      // Идентификатор набора символов
			OUT_TT_PRECIS,      // Точность вывода
			CLIP_DEFAULT_PRECIS,    // Точность отсечения
			ANTIALIASED_QUALITY,    // Качество вывода
			FF_DONTCARE|DEFAULT_PITCH,  // Семейство и Шаг
			"Courier New");      // Имя шрифта
	SelectObject(hDC_, font);        // Выбрать шрифт, созданный нами
	wglUseFontBitmaps(hDC_, 32, 96, base); // Построить 96 символов начиная с пробела
}

void OpenGL::InitGLScene(GLsizei Width, GLsizei Height)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
							// Очистка экрана в черный цвет
	glClearDepth(1.0);		// Разрешить очистку буфера глубины
	glDepthFunc(GL_LESS);	// Тип теста глубины
	glEnable(GL_DEPTH_TEST);// разрешить тест глубины
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);// разрешить плавное цветовое сглаживание
	glMatrixMode(GL_PROJECTION);// Выбор матрицы проекции
	glLoadIdentity();		// Сброс матрицы проекции
	gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
							// Вычислить соотношение геометрических размеров для окна
	glMatrixMode(GL_MODELVIEW);// Выбор матрицы просмотра модели
}

void OpenGL::DrawText(float x,float y,const char *fmt, ...)        // Заказная функция "Печати" GL
{
  char    text[256];      // Место для нашей строки
  va_list    ap;          // Указатель на список аргументов
  if (fmt == NULL)     // Если нет текста
    return;            // Ничего не делать
	
  va_start(ap, fmt);           // Разбор строки переменных
      vsprintf(text, fmt, ap); // И конвертирование символов в реальные коды
  va_end(ap);                  // Результат помещается в строку

  glDisable(GL_TEXTURE_2D);

  glLoadIdentity();
  glRasterPos2f(x,y);
  glPushAttrib(GL_LIST_BIT);      // Протолкнуть биты списка отображения ( НОВОЕ )
  glListBase(base - 32);          // Задать базу символа в 32 ( НОВОЕ )
  glCallLists(strlen(text), GL_UNSIGNED_BYTE, text); // Текст списками отображения ( НОВОЕ )
  glPopAttrib(); // Возврат битов списка отображения ( НОВОЕ )
  glEnable(GL_TEXTURE_2D);

}

void OpenGL::ReSizeGLScene(GLsizei Width, GLsizei Height)
{
	if (Height==0)		// Предотвращение деления на ноль, если окно слишком мало
		Height=1;

	glViewport(0, 0, Width, Height);
		// Сброс текущей области вывода и перспективных преобразований

	glMatrixMode(GL_PROJECTION);// Выбор матрицы проекций
	glLoadIdentity();			// Сброс матрицы проекции

	gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
		// Вычисление соотношения геометрических размеров для окна
	glMatrixMode(GL_MODELVIEW);	// Выбор матрицы просмотра модели
}
/*
void OpenGL::LoadGLTextures(GLuint texture[3])
{
	// Загрузка картинки
	AUX_RGBImageRec* text[2];

	for(int i=0;i<2;i++)
		text[i]=new AUX_RGBImageRec;

	//text=new AUX_RGBImageRec[3];
	text[0] = auxDIBImageLoad("Textures//Ship1.bmp");
	text[1] = auxDIBImageLoad("Textures//Ship2.bmp");
	// Создание текстуры
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