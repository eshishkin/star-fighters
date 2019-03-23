#include <windows.h>		// Заголовочный файл для Windows
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdarg.h>

/*OpenGL & OpenIL headers*/
#include <gl\gl.h>			
#include <gl\glu.h>			
#include "Libraries\glaux.h"
#include "Libraries\IL\il.h"
#include "Libraries\IL\ilu.h"

/*OpenGL & OpenIL libs*/
#pragma comment(lib,"Opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"Libraries\\lib\\Glaux.lib")
#pragma comment(lib,"Libraries\\lib\\DevIL.lib")
#pragma comment(lib,"Libraries\\lib\\ILU.lib")

#pragma comment(lib, "winmm.lib")

#define PI 3.1415926535898
#define _CRT_SECURE_NO_WARNINGS