#pragma once
#include "../Utilities/utilities.h"
#include <cstdio>
class Texture
{
private:
	
public:
	char mTgaFilePath[150];
	char wrap[50], filter1[50], filter2[50];
	GLenum mTiling;
	GLenum mWrap;
	GLenum mFilter1, mFilter2;
	void ConfigTexture();
	GLuint mTextureId;

	void Init();
	Texture();
	Texture(char* tgaFilePath, GLenum tiling = GL_REPEAT);
	~Texture();
	void Draw();
};