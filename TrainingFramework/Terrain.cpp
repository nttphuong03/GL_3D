#include "stdafx.h"
#include "Terrain.h"

void Terrain::Print() {
	Object::Print();
	printf("\ntiling: %d", tiling);
	printf("\nfog_start: %d, fog_length: %d, log_color: %f %f %f", fog_start, fog_length, fog_color.x, fog_color.y, fog_color.z);
}

Terrain::~Terrain() {

}

void Terrain::Draw(){}
Terrain::Terrain(){}
void Terrain::Init() {
	int status = shaderObj.Init(shaderObj.fileVS, shaderObj.fileFS);
	printf("\nstatus of shader in terrain: %d", status);
	modelObj.Init();

	for (int i = 0; i < textureNum; i++) {
		texturesObj[i].shader = shaderObj;
		texturesObj[i].Init();
		
	}
	texturesObj[0].SetUniformLocation("blendTexture");
	texturesObj[1].SetUniformLocation("texture1");
	texturesObj[2].SetUniformLocation("texture2");
	texturesObj[3].SetUniformLocation("texture3");	
}