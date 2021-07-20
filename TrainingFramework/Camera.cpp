#include "stdafx.h"
#include "Camera.h"
#include "Vertex.h"
#include <cstdio>
#include <iostream>
#include "Globals.h"

using namespace std; 
Camera::Camera() {
	movementSpeed = 1.0f;
	mouseSensitivity = 0.1f;

	float aspect = (float)Globals::screenWidth / Globals::screenHeight;
	mPerspectiveMatrix.SetPerspective(mFOV, aspect, mNear, mFar);

	Rx.SetIdentity(); Ry.SetIdentity(); Rz.SetIdentity();
	T.SetIdentity();

	updateCameraVectors();
}

Camera::Camera( Vector3 position, Vector3 up, Vector3 target):Camera() {
	this->position = position;
	this->worldUp = up;
	this->target = target;
}

void Camera::updateCameraVectors() {
	T.SetTranslation(position);
	zaxis =(position-target).Normalize();
	xaxis = worldUp.Cross(zaxis).Normalize();
	yaxis = zaxis.Cross(xaxis).Normalize();
}


void  Camera::MoveForward(GLfloat deltaTime) {
	Vector3 deltaMove = -(position - target).Normalize() * deltaTime * movementSpeed;
	position += deltaMove;
	target += deltaMove;
}
void  Camera::MoveBackward(GLfloat deltaTime) {
	Vector3 deltaMove = -(position - target).Normalize() * deltaTime * movementSpeed;
	position -= deltaMove;
	target -= deltaMove;
}
void  Camera::MoveLeft(GLfloat deltaTime) {
	Vector3 deltaMove = -(worldUp.Cross(zaxis)).Normalize() * deltaTime * movementSpeed;

	position -= deltaMove;
	target -= deltaMove;
}
void  Camera::MoveRight(GLfloat deltaTime) {
	Vector3 deltaMove = -(worldUp.Cross(zaxis)).Normalize() * deltaTime * movementSpeed;
	position += deltaMove;
	target += deltaMove;
}

void Camera::RotationAroundX(GLfloat deltaTime) {
	Vector4 rotationAxis = Vector4(1,0,0, 1) * GetViewMatrix();
	float angle = deltaTime * movementSpeed;
	Matrix rotation;
	rotation.SetIdentity();
	rotation = rotation.SetRotationAngleAxis(angle, rotationAxis.x, rotationAxis.y, rotationAxis.z);
	Vector4 localTarget = Vector4(0, 0, -(position - this->target).Length(), 1);
	Vector4 localNewTarget = localTarget * rotation;
	Vector4 worldNewTarget = localNewTarget * GetWorldMatrix();
	target = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
}
void Camera::RotationAroundY(GLfloat deltaTime) {
	Vector4 rotationAxis = Vector4(0, 1, 0, 1) * GetViewMatrix();
	float angle = deltaTime * movementSpeed;
	Matrix rotation;
	rotation.SetIdentity();
	rotation = rotation.SetRotationAngleAxis(angle, rotationAxis.x, rotationAxis.y, rotationAxis.z);
	Vector4 localTarget = Vector4(0, 0, -(position-this->target).Length(), 1);
	Vector4 localNewTarget = localTarget * rotation;
	Vector4 worldNewTarget = localNewTarget * GetWorldMatrix();
	target = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
}
void Camera::RotationAroundZ(GLfloat deltaTime) {
	Vector4 rotationAxis = Vector4(0, 0,1,  1) * GetViewMatrix();
	float angle = deltaTime * movementSpeed;
	Matrix rotation;
	rotation.SetIdentity();
	rotation = rotation.SetRotationAngleAxis(angle, rotationAxis.x, rotationAxis.y, rotationAxis.z);
	Vector4 localTarget = Vector4(0, 0, -(position - this->target).Length(), 1);
	Vector4 localNewTarget = localTarget * rotation;
	Vector4 worldNewTarget = localNewTarget * GetWorldMatrix();
	target = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
}


Matrix Camera::GetWorldMatrix() {
	Matrix R;
	R.SetIdentity();
	
	R.m[0][0] = xaxis.x, R.m[0][1] = xaxis.y, R.m[0][2] = xaxis.z;
	R.m[1][0] = yaxis.x, R.m[1][1] = yaxis.y, R.m[1][2] = yaxis.z;
	R.m[2][0] = zaxis.x, R.m[2][1] = zaxis.y, R.m[2][2] = zaxis.z;
	
	return R * T;
}
Matrix Camera::GetViewMatrix() {
	//front: xaxis, up: yaxis, right: zaxis
	Matrix view;
	view.m[0][0] = xaxis.x; view.m[1][0] = xaxis.y; view.m[2][0] = xaxis.z; view.m[3][0] = -position.Dot(xaxis);
	view.m[0][1] = yaxis.x; view.m[1][1] = yaxis.y; view.m[2][1] = yaxis.z; view.m[3][1] = -position.Dot(yaxis);
	view.m[0][2] = zaxis.x; view.m[1][2] = zaxis.y; view.m[2][2] = zaxis.z; view.m[3][2] = -position.Dot(zaxis);
	view.m[0][3] = 0      ; view.m[1][3] = 0      ; view.m[2][3] = 0      ; view.m[3][3] = 1;
	return view;
}

Matrix Camera::GetPerspectiveMatrix() {
	return mPerspectiveMatrix;
}

void Camera::Update() {
	updateCameraVectors();
}