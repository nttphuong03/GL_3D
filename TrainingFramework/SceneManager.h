#pragma once
#pragma once
#include "../Utilities/utilities.h"
#include <cstdio>
#include <GLES2/gl2.h>
#include "Camera.h"
#include "Light.h"
#include "Object.h"
#include <vector>
#include "ResourceManager.h"
using namespace std;

class SceneManager
{
private:
	

public:
	static SceneManager* sceneInstance;
	int objectNum, cameraNumber;

	Camera* cameras;
	Light* lights;
	vector<Object*> objectList;
	ResourceManager resource;

	SceneManager();
	static SceneManager* GetInstance();
	void Init(char* rmPath);
	~SceneManager();
	void readFile(FILE* file);
	void CreateAllObjects();
	void Draw();
	void Init();
	void Print();
};