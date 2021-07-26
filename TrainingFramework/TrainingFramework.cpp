// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include <iostream>
#include "Texture.h"
#include "../Model.h"
#include "MVP.h"
#include <math.h>
#include "Camera.h"

#include "SceneManager.h"
#include <vector>

using namespace std;


#define MOVE_FORWARD 1
#define MOVE_BACKWARD 1 << 1
#define MOVE_LEFT 1 << 2
#define MOVE_RIGHT 1 << 3
#define ROTATE_X 1 << 4
#define ROTATE_Y 1 << 5
#define ROTATE_Z 1 << 6
#define ROTATE_X_NEG 1 << 7
#define ROTATE_Y_NEG 1 << 8
#define ROTATE_Z_NEG 1 << 9


int keyPressed = 0;

GLuint vboId, iboId, textureId;
Shaders myShaders;
Model model;
vector<Texture> textures;
MVP* mvp;
Camera camera;
SceneManager* scene = SceneManager::GetInstance();


int Init(ESContext* esContext)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	
	scene->Init("../ResourcesPacket/SM.txt");

	camera = scene->cameras[0];

	//creation of shaders and program 
	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");

}

void Draw(ESContext* esContext)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	for (int i = 0; i < scene-> objectNum; i++)
	{
		Object* o = scene->objectList.at(i);
		o->Draw(camera);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);

}

void Update(ESContext* esContext, float deltaTime)
{
	
	if (keyPressed & ROTATE_X) {
		camera.RotationAroundX(deltaTime);
	}

	if (keyPressed & ROTATE_Y) {
		camera.RotationAroundY(deltaTime);
	}
	if (keyPressed & ROTATE_Z) {
		camera.RotationAroundZ(deltaTime);
	}
	if (keyPressed & ROTATE_X_NEG) {
		camera.RotationAroundX(-deltaTime);
	}

	if (keyPressed & ROTATE_Y_NEG) {
		camera.RotationAroundY(-deltaTime);
	}
	if (keyPressed & ROTATE_Z_NEG) {
		camera.RotationAroundZ(-deltaTime);
	}
	if (keyPressed & MOVE_FORWARD) {
		//TODO: move forward of camera
		camera.MoveForward(deltaTime);
	}

	if (keyPressed & MOVE_BACKWARD) {
		camera.MoveBackward(deltaTime);
	}

	if (keyPressed & MOVE_LEFT) {
		camera.MoveLeft(deltaTime);
	}

	if (keyPressed & MOVE_RIGHT) {
		camera.MoveRight(deltaTime);
	}
	camera.Update();
}

void Key(ESContext* esContext, unsigned char key, bool bIsPressed)
{
	if (bIsPressed) {
		if (key == VK_UP) {
			keyPressed = keyPressed | ROTATE_X;
			return;
		}

		if (key == VK_DOWN) {
			keyPressed = keyPressed | ROTATE_X_NEG;
			return;
		}

		if (key == VK_LEFT) {
			keyPressed = keyPressed | ROTATE_Y;
			return;
		}
		if (key == VK_RIGHT) {
			keyPressed = keyPressed | ROTATE_Y_NEG;
			return;
		}
		if (key == 'a' || key == 'A') {
			keyPressed = keyPressed | MOVE_LEFT;
			return;
		}
		if (key == 'w' || key == 'W') {
			keyPressed = keyPressed | MOVE_FORWARD;
			return;
		}
		if (key == 's' || key == 'S') {
			keyPressed = keyPressed | MOVE_BACKWARD;
			return;
		}
		if (key == 'd' || key == 'D') {
			keyPressed = keyPressed | MOVE_RIGHT;
			return;
		}
		if (key == 'z' || key == 'Z') {
			keyPressed = keyPressed | ROTATE_Z;
			return;
		}
		if (key == 'v' || key == 'V') {
			keyPressed = keyPressed | ROTATE_Z_NEG;
			return;
		}
	}
	else {
		if (key == VK_UP) {
			keyPressed = keyPressed ^ ROTATE_X;
			return;
		}

		if (key == VK_DOWN) {
			keyPressed = keyPressed ^ ROTATE_X_NEG;
			return;
		}

		if (key == VK_LEFT) {
			keyPressed = keyPressed ^ ROTATE_Y;
			return;
		}
		if (key == VK_RIGHT) {
			keyPressed = keyPressed ^ ROTATE_Y_NEG;
			return;
		}
		if (key == 'a' || key == 'A') {
			keyPressed = keyPressed ^ MOVE_LEFT;
			return;
		}
		if (key == 'w' || key == 'W') {
			keyPressed = keyPressed ^ MOVE_FORWARD;
			return;
		}
		if (key == 's' || key == 'S') {
			keyPressed = keyPressed ^ MOVE_BACKWARD;
			return;
		}
		if (key == 'd' || key == 'D') {
			keyPressed = keyPressed ^ MOVE_RIGHT;
			return;
		}
		if (key == 'z' || key == 'Z') {
			keyPressed = keyPressed ^ ROTATE_Z;
			return;
		}
		if (key == 'v' || key == 'V') {
			keyPressed = keyPressed ^ ROTATE_Z_NEG;
			return;
		}
	}
}

void CleanUp()
{
	for (int i = 0; i < scene->objectNum; i++)
	{
		Object* o = scene->objectList.at(i);
		o->CleanUp();
	}
	scene->~SceneManager();
	glDeleteBuffers(1, &vboId);
	glDeleteBuffers(1, &iboId);
	
}

int _tmain(int argc, TCHAR* argv[])
{
	ESContext esContext;

	esInitContext(&esContext);

	esCreateWindow(&esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if (Init(&esContext) != 0)
		return 0;

	esRegisterDrawFunc(&esContext, Draw);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterKeyFunc(&esContext, Key);

	

	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}