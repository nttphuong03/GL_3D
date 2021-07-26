#include "stdafx.h"
#include "Lighting.h"

void Lighting::Print() {
	Object::Print();
	printf("\nambient_weight: %d, spce_power: %d", ambient_weight, spec_power);
}
void Lighting::Draw() {

}


void Lighting::Init() {
	int status = shaderObj.Init(shaderObj.fileVS, shaderObj.fileFS);
	modelObj.Init();

	for (int i = 0; i < textureNum; i++) {
		texturesObj[i].Init();
		texturesObj[i].shader = shaderObj;
		texturesObj[i].SetUniformLocation("u_texture");

	}

}

Lighting::Lighting(){}
Lighting::~Lighting(){}