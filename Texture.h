#ifndef TEXTURE_H
#define TEXTURE_H

#include "stdafx.h"

typedef struct TextureImage
{
    GLubyte *imageData;     // ������ ��������
    GLuint  bpp;            // ���� �� ������
    GLuint width,height;        // ������ � ������
    GLuint texID;           // ID ��������
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