#ifndef TEXTURE_H
#define TEXTURE_H

#include "stdafx.h"

typedef struct TextureImage
{
    GLubyte *imageData;     // Данные текстуры
    GLuint  bpp;            // Байт на пиксел
    GLuint width,height;        // Высота и ширина
    GLuint texID;           // ID текстуры
} TextureImage;

class CTexture
{
	public:
		CTexture();
		~CTexture();
		void LoadTexture(ILenum FileType, char *filename, TextureImage *texture);
		void FreeTexture(TextureImage *texture);
};

#endif