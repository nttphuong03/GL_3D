#pragma once
#include "../Utilities/utilities.h"
#include <cstdio>
#include <GLES2/gl2.h>

class Model
{
public:
	char modelFile[70];
	float scale;
	float offset;
	bool InitNFG(FILE* file);
	GLuint mVBO;
	GLuint mIBO;
	int mNumberOfIndices;
	

	Model();
	Model(char* modelFile);
	~Model();
	void Init();
};