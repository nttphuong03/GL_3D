#include "stdafx.h"
#include "Texture.h"
#include <iostream>
#include <string>


using namespace std;

void Texture::ConfigTexture()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::Init()
{
	//create texture resource
	glGenTextures(1, &mTextureId);

	//bind texture to the 2D texture type
	glBindTexture(GL_TEXTURE_2D, mTextureId);

	//create CPU buffer and load it from image data
	int iWidth = 0;
	int iHeight = 0;
	int iBpp = 0;
	
	const char* imageData = LoadTGA(mTgaFilePath, &iWidth, &iHeight, &iBpp);

	GLenum format = (iBpp == 24 ? GL_RGB : GL_RGBA);

	//load the image data into texture resource
	glTexImage2D(GL_TEXTURE_2D, 0, format, iWidth, iHeight, 0, format, GL_UNSIGNED_BYTE, imageData);

	

	if (imageData)
	{
		//std::cout << "Load texture succes" << std::endl;
		glTexImage2D(GL_TEXTURE_2D, 0, format, iWidth, iHeight, 0, format, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Fail to load texture: " <<mTgaFilePath<< std::endl;
	}
	
	//free client memory
	delete[] imageData;

	ConfigTexture();
	
	//call SetUnifromLocation after Init.
}

void Texture::SetUniformLocation(char* name) {
	uniformLocation = glGetUniformLocation(shader.program, name);
}
Texture::Texture(char* path, GLenum tiling)
{
	int j = 0;
	while (path[j] != '\0') {
		mTgaFilePath[j] = path[j];
		j++;
	}
	mTiling = tiling;
}
Texture::Texture() {}

Texture::~Texture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
