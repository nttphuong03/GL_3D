#include "stdafx.h"
#include "ResourceManager.h"

ResourceManager* ResourceManager::resourceIns = NULL;
ResourceManager::ResourceManager() {

}
ResourceManager* ResourceManager::GetInstance() {
	if (!resourceIns) {
		resourceIns = new ResourceManager();
	}
	return resourceIns;
}
void ResourceManager::readFile(FILE* file) {
	fscanf(file, "#Models: %d\n", &modelNumber);

	for (int i = 0; i < modelNumber; i++) {
		Model m = Model();
		int id;
		fscanf(file, "ID %d\n", &id);
		fscanf(file, "FILE %s\n", m.modelFile);

		if (id == 3) {
			fscanf(file, "SCALE %f\n", &m.scale);
			fscanf(file, "OFFSET %f\n", &m.offset);
		}

		models.push_back(m);
	}
	fscanf(file, "\n");

	fscanf(file, "#2D Textures: %d\n", &textureNumber);
	for (int i = 0; i < textureNumber; i++) {
		Texture t = Texture();
		int id;
		

		fscanf(file, "ID %d\n", &id);
		fscanf(file, "FILE %s\n", t.mTgaFilePath);
		fscanf(file, "WRAP %s\n", t.wrap);
		fscanf(file, "FILTER %s %s\n", t.filter1, t.filter2);

		textures.push_back(t);
	}
	fscanf(file, "\n");

	fscanf(file, "#Cube Textures: %d\n", &cubeNumber);

	for (int i = 0; i < cubeNumber; i++) {
		Texture t = Texture();
		int id;

		fscanf(file, "ID %d\n", &id);
		fscanf(file, "FILE %s\n", t.mTgaFilePath);
		fscanf(file, "WRAP %s\n", t.wrap);
		fscanf(file, "FILTER %s %s\n", t.filter1, t.filter2);

		cubes.push_back(t);
	}
	fscanf(file, "\n");

	fscanf(file, "#Shaders: %d\n", &shaderNumber);

	for (int i = 0; i < shaderNumber; i++) {
		Shaders shader = Shaders();
		int id;
		int state;

		fscanf(file, "ID %d\n", &id);
		fscanf(file, "VS %s\n", shader.fileVS);
		fscanf(file, "FS %s\n", shader.fileFS);
		fscanf(file, "STATES %d\n", &state);
		fscanf(file, "GL_DEPTH_TEST %d\n", &shader.depth_test);
		fscanf(file, "GL_CULL_FACE %d\n", &shader.cull_face);

		if (state == 3) {
			fscanf(file, "GL_BLEND %d\n", &shader.blend);
			fscanf(file, "%s %s\n", shader.src_alpha, shader.scr_one);
		}
		
		shaders.push_back(shader);
	}
	
}


void ResourceManager::Init(char* rmPath) {

	FILE* file = fopen(rmPath, "rb");
	if (file != NULL)
	{
		readFile(file);
		fclose(file);
	}
	else {
		printf("\n!!!!!!!!!!!!!!!!!!error read file in resource manager!!!!!!!!!!!\n");
	}
}
ResourceManager::~ResourceManager(){}

void ResourceManager::Print() {
	for (int i = 0; i < modelNumber; i++) {
		Model m = models.at(i);
		printf("\n%s", m.modelFile);
	}
	for (int i = 0; i < textureNumber; i++) {
		Texture t = textures.at(i);

		int j = 0;
		while (t.mTgaFilePath[j] != '\0') {
			printf("%c", t.mTgaFilePath[j]);
			j++;
		}
		printf("\n");
	}
}