#include <stdafx.h>
#include "Model.h"
#include <string.h>
#include <conio.h>
#include <cstdio>
#include "TrainingFramework/Vertex.h"

int Model::Init(char* fileModel) {
	this->fileModel = fileModel;
	FILE* file = fopen(fileModel, "rb");
	if (file == NULL) {
		printf("\nload model file error\n");
		return 0;
	}
	
	readFile(file);

	return 1;
}

int Model::readFile(FILE* file) {
	int verticalNumber;
	fscanf(file, "NrVertices: %d\n ", &verticalNumber);
	if (verticalNumber <= 0) {
		return 0;
	}
	printf("%d\n", verticalNumber);

	Vertex* vertices = new Vertex[verticalNumber];
	for (int i = 0; i < verticalNumber; i++) {
		float posX, posY, posZ;
		float normX, normY, normZ;
		float binormX, binormY, binormZ;
		float tgtX, tgtY, tgtZ;
		float uvX, uvY;

		int id;

		fscanf(file, "%d. ", &id);
		fscanf(file, "pos:[%f, %f, %f]; ", &posX, &posY, &posZ);
		fscanf(file, "norm:[%f, %f, %f]; ", &normX, &normY, &normZ);
		fscanf(file, "binorm:[%f, %f, %f]; ", &binormX, &binormY, &binormZ);
		fscanf(file, "tgt:[%f, %f, %f]; ", &tgtX, &tgtY, &tgtZ);
		fscanf(file, "uv:[%f, %f];\n   ", &uvX, &uvY);

		vertices[i].pos.x = posX; vertices[i].pos.y = posY -1; vertices[i].pos.z = posZ;
		vertices[i].uv.x = uvX; vertices[i].uv.y = uvY;

		//printf("%d %f %f %f %f %f\n", id, posX, posY, posZ, uvX, uvY);
	}
	glGenBuffers(1, &this->mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * verticalNumber, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	int indicesNumber;
	fscanf(file, "NrIndices: %d", &indicesNumber);
	
	if (indicesNumber <= 0) {
		glDeleteBuffers(1, &mVBO);
		return 0;
	}

	int* indices = new int[indicesNumber];
	for (int i = 0; i < indicesNumber; i += 3) {
		int id;
		int iX, iY, iZ;
		fscanf(file, "%d. ", &id);
		fscanf(file, " %d, %d, %d\n", &iX, &iY, &iZ);

		indices[i] = iX;
		indices[i+1] = iY;
		indices[i+2] = iZ;
		//printf("%d %d %d\n", iX, iY, iZ);
	}

	glGenBuffers(1, &this->mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indicesNumber, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	this->indicesNumber = indicesNumber;

	fclose(file);
	return 1;
}

Model::~Model()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &mVBO);
	glDeleteBuffers(1, &mIBO);
}