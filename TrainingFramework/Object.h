#pragma once
#include "../Utilities/utilities.h"
#include <cstdio>
#include <GLES2/gl2.h>
#include "../Model.h"
#include "Texture.h"
#include "Shaders.h"
#include <vector>

using namespace std;

class Object {
public:
	int modelIndex, textureNum, lightNum, cubeTexNum;
	int* textures, *lights, *cubeTextures;
	int cubeTexture, shader;

	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	Model modelObj;
	vector<Texture> texturesObj;
	vector<Texture> cubeTexturesObj;
	Shaders shaderObj;


	Object();
	virtual void Draw();
	virtual void Print();
	void Init();
	Matrix GetModelMatrix();

};