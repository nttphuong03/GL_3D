#pragma once
#include "../Utilities/utilities.h"
#include <cstdio>
#include <GLES2/gl2.h>
#include <math.h>
#include "Shaders.h"
#include "Globals.h"

class Camera
{
public:
	Vector3 position;
	Vector3 target;
	Vector3 worldUp;
	Vector3 xaxis;
	Vector3 yaxis;
	Vector3 zaxis;

	float mFOV = 1.0f;
	float mNear = 0.1f;
	float mFar = 1000.0f;

	//camera options
	float movementSpeed;
	float mouseSensitivity;
	float rotateSpeed;

	Matrix mPerspectiveMatrix;

	Matrix T;

	Camera();
	Camera( Vector3 position, Vector3 up = Vector3(0.0f, 1.0f, 0.0f), Vector3 target = Vector3(0.0f, 0.0f, 0.0f));
	Camera(Vector3 position, Vector3 up, Vector3 target, float fov, float mNear, float mFar, float move_speed, float rotate_speed) {
		this->position = position;
		this->worldUp = up;
		this->target = target;
		this->mFOV = fov;
		this->mNear = mNear;
		this->mFar = mFar;
		this->movementSpeed = move_speed/2;
		this->rotateSpeed = rotate_speed;
		
		float aspect = (float)Globals::screenWidth / Globals::screenHeight;
		mPerspectiveMatrix.SetPerspective(mFOV, aspect, mNear, mFar);

		T.SetIdentity();

		updateCameraVectors();
	}

	void MoveForward(GLfloat deltaTime);
	void MoveBackward(GLfloat deltaTime);
	void MoveLeft(GLfloat deltaTime);
	void MoveRight(GLfloat deltaTime);

	void RotationAroundX(GLfloat deltaTime);
	void RotationAroundY(GLfloat deltaTime);
	void RotationAroundZ(GLfloat deltaTime);
	void Rotation();
	void Update();

	Matrix GetViewMatrix();
	Matrix GetPerspectiveMatrix();
	Matrix GetWorldMatrix();

private:
	void updateCameraVectors();
	float limitAngle(float angle);
};