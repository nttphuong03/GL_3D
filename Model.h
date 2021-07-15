#pragma once
#include "../Utilities/utilities.h"

class Model
{
public:
	char* fileModel;
	GLuint mVBO;
	GLuint mIBO;
	int indicesNumber;

	int Init(char* fileModel);
	int readFile(FILE* file);
	~Model();
};