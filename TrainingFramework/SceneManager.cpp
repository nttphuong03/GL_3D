#include "stdafx.h"
#include <string.h>
#include <conio.h>
#include "SceneManager.h"
#include "Terrain.h"
#include "Lighting.h";
#include "NormalMapping.h"

SceneManager* SceneManager::sceneInstance = NULL;
SceneManager* SceneManager::GetInstance() {
	if (! sceneInstance) {
		sceneInstance = new SceneManager();
	}
	return sceneInstance;
 }
void SceneManager::readFile(FILE* file) {
	printf("\n!!!!!!!!!!!!!!!!!!inside read file in scene!!!!!!!!!!!\n");
	resource = ResourceManager();
	resource.Init("../ResourcesPacket/RM.txt");

	
	fscanf(file, "#Cameras: %d\n", &cameraNumber);

	if (cameraNumber < 0) {
		printf("no came \n");
	}
	else {
		this->cameras = new Camera[cameraNumber];
		for (int i = 0; i < cameraNumber; i++) {
			int id;
			float px, py, pz, tx, ty, tz, ux, uy, uz;
			float fov, mNear, mFar, move_speed, rotate_speed;
			
			fscanf(file, "ID %d\n", &id);
			fscanf(file, "POSITION %f %f %f\n", &px, &py, &pz);
			fscanf(file, "TARGET %f %f %f\n", &tx, &ty, &tz);
			fscanf(file, "UP %f %f %f\n", &ux, &uy, &uz);
			fscanf(file, "FOVY %f\n", &fov);
			fscanf(file, "NEAR %f\n", &mNear);
			fscanf(file, "FAR %f\n", &mFar);
			fscanf(file, "MOVE_SPEED %f\n", &move_speed);
			fscanf(file, "ROTATE_SPEED %f\n", &rotate_speed);
			fscanf(file, "\n");
			cameras[i] = Camera(Vector3(px, py, pz), Vector3(ux, uy, uz), Vector3(tx, ty, tz), fov, mNear, mFar, move_speed, rotate_speed);

		}
	}

	//readlight
	int lightNumber;
	fscanf(file, "#Lights: %d\n", &lightNumber);
	if (lightNumber < 0) {
		printf("light is neg\n");
	}
	else {
		this->lights = new Light[lightNumber];
		for (int i = 0; i < lightNumber; i++) {
			int id;
			float px, py, pz, color_x, color_y, color_z;
			char type [25];

			fscanf(file, "ID %d\n", &id);
			fscanf(file, "TYPE %s\n", type);
			fscanf(file, "POS_DIR %f %f %f\n", &px, &py, &pz);
			fscanf(file, "COLOR %f %f %f\n", &color_x, &color_y, &color_z);
			fscanf(file, "\n");

			lights[id] = Light(type, Vector3(px, py, pz), Vector3(color_x, color_y, color_z));
		}
	}
	
	
	
	char cmt[25];
	fscanf(file, "#Objects: %d\n", &objectNum);
	
	printf("\n___________read %d object in scene_________", objectNum);

	//if (objectNum < 0) return;
	for (int i = 0; i < objectNum; i++) {
		int id;
		fscanf(file, "ID %d //%s\n", &id, cmt);

		if (id == 3) {
			//read terrain;
			Terrain* t = new Terrain();
			fscanf(file, "MODEL %d\n", &t->modelIndex);
			t->modelObj = resource.models.at(t->modelIndex);

			fscanf(file, "TEXTURES %d\n", &t->textureNum);

			t->textures = new int[t->textureNum];
			for (int j = 0; j < t->textureNum; j++) {
				fscanf(file, "TEXTURE %d\n", &t->textures[j]);
				t->texturesObj.push_back(resource.textures.at(t->textures[j]));
			}

			fscanf(file, "CUBETEXTURES %d\n", &t->cubeTexNum);

			t->cubeTextures = new int[t->cubeTexNum];
			for (int j = 0; j < t->cubeTexNum; j++) {
				fscanf(file, "TEXTURE %d\n", &t->cubeTextures[j]);
				t->cubeTexturesObj.push_back(resource.cubes.at(t->cubeTextures[j]));
			}

			fscanf(file, "SHADER %d\n", &t->shader);
			t->shaderObj = resource.shaders.at(t->shader);
			

			fscanf(file, "LIGHTS %d\n", &t->lightNum);
			

			t->lights = new int[t->lightNum];
			for (int j = 0; j < t->lightNum; j++) {
				fscanf(file, "LIGHT %d\n", &t->lights[j]);
			}

			fscanf(file, "POSITION %f %f %f\n", &t->position.x, &t->position.y, &t->position.z);

			fscanf(file, "ROTATION %f %f %f\n", &t->rotation.x, &t->rotation.y, &t->rotation.z);

			fscanf(file, "SCALE %f %f %f\n", &t->scale.x, &t->scale.y, &t->scale.z);

			fscanf(file, "TILING %d\n", &t->tiling);

			fscanf(file, "FOG_START %d\n", &t->fog_start);

			fscanf(file, "FOG_LENGTH  %d\n", &t->fog_length);

			fscanf(file, "FOG_COLOR %f %f %f\n", &t->fog_color.x, &t->fog_color.y, &t->fog_color.z);

			fscanf(file, "\n");

			
			this->objectList.push_back(t);

		}

		else if (id == 6) {
			//read lighting;
			Lighting* t = new Lighting(); 
			fscanf(file, "MODEL %d\n", &t->modelIndex);
			t->modelObj = resource.models.at(t->modelIndex);

			fscanf(file, "TEXTURES %d\n", &t->textureNum);

			t->textures = new int[t->textureNum];
			for (int j = 0; j < t->textureNum; j++) {
				fscanf(file, "TEXTURE %d\n", &t->textures[j]);
				t->texturesObj.push_back(resource.textures.at(t->textures[j]));
			}

			fscanf(file, "CUBETEXTURES %d\n", &t->cubeTexNum);

			t->cubeTextures = new int[t->cubeTexNum];
			for (int j = 0; j < t->cubeTexNum; j++) {
				fscanf(file, "TEXTURE %d\n", &t->cubeTextures[j]);
				t->cubeTexturesObj.push_back(resource.cubes.at(t->cubeTextures[j]));
			}

			fscanf(file, "SHADER %d\n", &t->shader);
			t->shaderObj = resource.shaders.at(t->shader);


			fscanf(file, "LIGHTS %d\n", &t->lightNum);


			t->lights = new int[t->lightNum];
			for (int j = 0; j < t->lightNum; j++) {
				fscanf(file, "LIGHT %d\n", &t->lights[j]);
			}

			fscanf(file, "POSITION %f %f %f\n", &t->position.x, &t->position.y, &t->position.z);

			fscanf(file, "ROTATION %f %f %f\n", &t->rotation.x, &t->rotation.y, &t->rotation.z);

			fscanf(file, "SCALE %f %f %f\n", &t->scale.x, &t->scale.y, &t->scale.z);
			fscanf(file, "AMBIENT_WEIGHT %f\n", &t->ambient_weight);
			fscanf(file, "SPEC_POWER %f\n", &t->spec_power);

			

			fscanf(file, "\n");

			this->objectList.push_back(t);
		}
		else if (id == 7) {
			Mapping* t = new Mapping();

			fscanf(file, "MODEL %d\n", &t->modelIndex);
			t->modelObj = resource.models.at(t->modelIndex);

			fscanf(file, "TEXTURES %d\n", &t->textureNum);


			t->textures = new int[t->textureNum];
			for (int j = 0; j < t->textureNum; j++) {
				fscanf(file, "TEXTURE %d\n", &t->textures[j]);
				t->texturesObj.push_back(resource.textures.at(t->textures[j]));
			}

			fscanf(file, "CUBETEXTURES %d\n", &t->cubeTexNum);

			t->cubeTextures = new int[t->cubeTexNum];
			for (int j = 0; j < t->cubeTexNum; j++) {
				fscanf(file, "TEXTURE %d\n", &t->cubeTextures[j]);
				t->cubeTexturesObj.push_back(resource.cubes.at(t->cubeTextures[j]));
			}

			fscanf(file, "SHADER %d\n", &t->shader);
			t->shaderObj = resource.shaders.at(t->shader);


			fscanf(file, "LIGHTS %d\n", &t->lightNum);


			t->lights = new int[t->lightNum];
			for (int j = 0; j < t->lightNum; j++) {
				fscanf(file, "LIGHT %d\n", &t->lights[j]);
			}

			fscanf(file, "POSITION %f %f %f\n", &t->position.x, &t->position.y, &t->position.z);

			fscanf(file, "ROTATION %f %f %f\n", &t->rotation.x, &t->rotation.y, &t->rotation.z);

			fscanf(file, "SCALE %f %f %f\n", &t->scale.x, &t->scale.y, &t->scale.z);
			fscanf(file, "AMBIENT_WEIGHT %f\n", &t->ambient_weight);
			fscanf(file, "SPEC_POWER %f\n", &t->spec_power);

			

			fscanf(file, "\n");

			this->objectList.push_back(t);
		}
		else {
			Object* t = new Object();

			fscanf(file, "MODEL %d\n", &t->modelIndex);
			t->modelObj = resource.models.at(t->modelIndex);

			fscanf(file, "TEXTURES %d\n", &t->textureNum);


			t->textures = new int[t->textureNum];
			for (int j = 0; j < t->textureNum; j++) {
				fscanf(file, "TEXTURE %d\n", &t->textures[j]);
				t->texturesObj.push_back(resource.textures.at(t->textures[j]));
			}

			fscanf(file, "CUBETEXTURES %d\n", &t->cubeTexNum);

			t->cubeTextures = new int[t->cubeTexNum];
			for (int j = 0; j < t->cubeTexNum; j++) {
				fscanf(file, "TEXTURE %d\n", &t->cubeTextures[j]);
				t->cubeTexturesObj.push_back(resource.cubes.at(t->cubeTextures[j]));
			}

			fscanf(file, "SHADER %d\n", &t->shader);
			t->shaderObj = resource.shaders.at(t->shader);

			fscanf(file, "LIGHTS %d\n", &t->lightNum);


			t->lights = new int[t->lightNum];
			for (int j = 0; j < t->lightNum; j++) {
				fscanf(file, "LIGHT %d\n", &t->lights[j]);
			}

			fscanf(file, "POSITION %f %f %f\n", &t->position.x, &t->position.y, &t->position.z);

			fscanf(file, "ROTATION %f %f %f\n", &t->rotation.x, &t->rotation.y, &t->rotation.z);

			fscanf(file, "SCALE %f %f %f\n", &t->scale.x, &t->scale.y, &t->scale.z);
			
			fscanf(file, "\n");
			objectList.push_back(t);
		}
	}
}
void SceneManager::Init(char* rmPath) {


	FILE* file = fopen(rmPath, "rb");
	if (file != NULL)
	{
		readFile(file);
		fclose(file);

		Init();
	}
	else {
		printf("\n!!!!!!!!!!!!!!!!!!error read file in scene!!!!!!!!!!!\n");
	}
}
SceneManager::~SceneManager() {
	delete[] cameras;
	delete[] lights;
}

SceneManager::SceneManager() {
	
}



void SceneManager::Init() {
	
	for (int j = 0; j < objectList.size(); j++) {
		Object* o = objectList.at(j);
		Terrain* t = dynamic_cast<Terrain*>(o);
		Lighting* l = dynamic_cast<Lighting*>(o);
		Mapping* m = dynamic_cast<Mapping*>(o);
		if (t != nullptr) {
			t->Init();
		}
		else if (l != nullptr) {
			l->Init();
		}
		else if (m != nullptr) {
			m->Init();
		}
		else {
			o->Init();
		}
	}
}
void SceneManager::Print() {
	for (int j = 0; j < objectList.size() ;j++) {
		
		printf("\ntextureNumber: %d", objectList.at(j)->textureNum);
		for (int i = 0; i < objectList.at(j)->textureNum; i++) {
			printf("\nfile texture %s", objectList.at(j)->texturesObj[i].mTgaFilePath);
		}
		printf("\n");
	
			printf("\nfileModel: %s", objectList.at(j)->modelObj.modelFile);
	
	}
}