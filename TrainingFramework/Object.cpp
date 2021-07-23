#include "stdafx.h"
#include "Object.h"

void Object::Print() {
	printf("\nModel: %d", modelIndex);
	printf("\ntextureNum: %d", textureNum);
	printf("\ncubeTextureNum: %d", cubeTexNum);
	printf("\nshaderIndex: %d", shader);
	printf("\nlightsNum: %d", lightNum);
	printf("\nposition: %f, %f, %f", position.x, position.y, position.z);
	printf("\nrotation: %f, %f, %f", rotation.x, rotation.y, rotation.z);
	printf("\nscale: %f, %f, %f", scale.x, scale.y, scale.z);
	printf("\nfileModel: %s", modelObj.modelFile);
	
}
void Object::Draw() {
	//draw model and texture.
	modelObj.Draw();
	for (int i = 0; i < textureNum; i++) {
		texturesObj[i].Draw();
	}
}
void Object::Init() {
	modelObj.Init();
	
	for (int i = 0; i < textureNum; i++) {
		texturesObj[i].Init();
	
	}
}

Object::Object(){}

Matrix Object::GetModelMatrix() {
	Matrix T, S;

	T.SetTranslation(position);
	S.SetScale(scale.x, scale.y, scale.z);

	Matrix Rx, Ry, Rz;
	Rx.SetRotationX(rotation.x);
	Ry.SetRotationY(rotation.y);
	Rz.SetRotationZ(rotation.z);
	Matrix R =  Rz * Rx * Ry;

	return S * R * T;

}