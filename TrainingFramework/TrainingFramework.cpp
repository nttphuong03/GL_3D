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

#define MOVE_FORWARD 1
#define MOVE_BACKWARD 1 << 1
#define MOVE_LEFT 1 << 2
#define MOVE_RIGHT 1 << 3
#define ROTATE_X 1 << 4
#define ROTATE_Y 1 << 5
#define ROTATE_Z 1 << 6


int keyPressed = 0;

GLuint vboId, iboId, textureId;
Shaders myShaders;
Model* model;
Texture* texture;
MVP* mvp;
Camera* camera = new Camera( Vector3(0.0f, 0.0f, 3.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f,0.0f,0.0f));


int Init(ESContext* esContext)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Texture
	texture = new Texture("../ResourcesPacket/Textures/Woman1.tga");
	texture->Init();
	glBindTexture(GL_TEXTURE_2D, texture->mTextureId);

	//Model
	model = new Model("../ResourcesPacket/Models/Woman1.nfg");
	model->Init();
	glBindBuffer(GL_ARRAY_BUFFER, model->mVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->mIBO);

	//creation of shaders and program 
	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");

}

void Draw(ESContext* esContext)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(myShaders.program);

	glBindTexture(GL_TEXTURE_2D, texture->mTextureId);
	//glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBindBuffer(GL_ARRAY_BUFFER, model->mVBO);

	mvp = new MVP(myShaders);
	mvp->Transform(camera->GetViewMatrix(), camera->GetPerspectiveMatrix());

	delete(mvp);

	if (myShaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.positionAttribute);
		glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	if (myShaders.colorAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.colorAttribute);
		glVertexAttribPointer(myShaders.colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vector3));
	}

	if (myShaders.uvAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.uvAttribute);
		glVertexAttribPointer(myShaders.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(Vector3)));
	}
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->mIBO);

	glDrawElements(GL_TRIANGLES, model->mNumberOfIndices, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update(ESContext* esContext, float deltaTime)
{
	if (keyPressed & MOVE_FORWARD) {
		//TODO: move forward of camera
		camera->MoveForward(deltaTime);
	}

	if (keyPressed & MOVE_BACKWARD) {
		camera->MoveBackward(deltaTime);
	}

	if (keyPressed & MOVE_LEFT) {
		camera->MoveLeft(deltaTime);
	}

	if (keyPressed & MOVE_RIGHT) {
		camera->MoveRight(deltaTime);
	}
	if (keyPressed & ROTATE_X) {
		camera->RotationAroundX(deltaTime);
	}

	if (keyPressed & ROTATE_Y) {
		camera->RotationAroundY(deltaTime);
	}
	if (keyPressed & ROTATE_Z) {
		camera->RotationAroundZ(deltaTime);
	}
	camera->Update();
}

void Key(ESContext* esContext, unsigned char key, bool bIsPressed)
{
	if (bIsPressed) {
		if (key == VK_UP) {
			keyPressed = keyPressed | MOVE_FORWARD;
			return;
		}

		if (key == VK_DOWN) {
			keyPressed = keyPressed | MOVE_BACKWARD;
			return;
		}

		if (key == VK_LEFT) {
			keyPressed = keyPressed | MOVE_LEFT;
			return;
		}
		if (key == VK_RIGHT) {
			keyPressed = keyPressed | MOVE_RIGHT;
			return;
		}
		if (key == 'x' || key == 'X') {
			keyPressed = keyPressed | ROTATE_X;
			return;
		}
		if (key == 'y' || key == 'Y') {
			keyPressed = keyPressed | ROTATE_Y;
			return;
		}
		if (key == 'z' || key == 'Z') {
			keyPressed = keyPressed | ROTATE_Z;
			return;
		}
	}
	else {
		if (key == VK_UP) {
			keyPressed = keyPressed ^ MOVE_FORWARD;
			return;
		}

		if (key == VK_DOWN) {
			keyPressed = keyPressed ^ MOVE_BACKWARD;
			return;
		}

		if (key == VK_LEFT) {
			keyPressed = keyPressed ^ MOVE_LEFT;
			return;
		}
		if (key == VK_RIGHT) {
			keyPressed = keyPressed ^ MOVE_RIGHT;
			return;
		}
		if (key == 'x' || key == 'X') {
			keyPressed = keyPressed ^ ROTATE_X;
			return;
		}
		if (key == 'y' || key == 'Y') {
			keyPressed = keyPressed ^ ROTATE_Y;
			return;
		}
		if (key == 'z' || key == 'Z') {
			keyPressed = keyPressed ^ ROTATE_Z;
			return;
		}
	}
}

void CleanUp()
{
	glDeleteBuffers(1, &vboId);
	glDeleteBuffers(1, &iboId);
	model->~Model();
	delete model;
	texture->~Texture();
	delete texture;
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