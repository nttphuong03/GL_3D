#pragma once
#pragma once
#include "../Utilities/utilities.h"
#include <cstdio>
#include <GLES2/gl2.h>
#include <vector>
#include "../Model.h"
#include "Texture.h"
#include "Shaders.h"
#include <vector>

using namespace std;

class ResourceManager
{

public:
	static ResourceManager* resourceIns;

	int modelNumber, textureNumber, shaderNumber, cubeNumber;
	vector<Model> models;
	vector<Texture> textures;
	vector<Texture> cubes;
	vector<Shaders> shaders;
	
	ResourceManager();
	static ResourceManager* GetInstance();

	void readFile(FILE* file);

	void Init(char* rmPath);
	~ResourceManager();
	void Print();
};