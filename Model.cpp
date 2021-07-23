#include "stdafx.h"
#include "Model.h"
#include <string.h>
#include <conio.h>
#include "TrainingFramework/Vertex.h"
#include <string>


using namespace std;

bool Model::InitNFG(FILE* file)
{
	int numberOfVertices;
	fscanf(file, "NrVertices: %d\n", &numberOfVertices);
	if (numberOfVertices <= 0)
		return false;
	Vertex* vertices = new Vertex[numberOfVertices];
	for (int i = 0; i < numberOfVertices; ++i)
	{
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
		fscanf(file, "uv:[%f, %f];\n ", &uvX, &uvY);
		(vertices + i)->pos.x = posX; (vertices + i)->pos.y = posY - 1; (vertices + i)->pos.z = posZ;
		(vertices + i)->coords.x = uvX; (vertices + i)->coords.y = uvY;
	}
	glGenBuffers(1, &this->mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numberOfVertices, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	int numberOfIndices;
	fscanf(file, "NrIndices: %d\n", &numberOfIndices);
	if (numberOfIndices <= 0)
	{
		glDeleteBuffers(1, &mVBO);
		return 0;
	}
	int* indices = new int[numberOfIndices];
	for (int i = 0; i < numberOfIndices; i += 3)
	{
		int id;
		int iX, iY, iZ;
		fscanf(file, "%d. ", &id);
		fscanf(file, " %d, %d, %d\n", &iX, &iY, &iZ);
		*(indices + i) = iX; *(indices + i + 1) = iY; *(indices + i + 2) = iZ;
	}
	glGenBuffers(1, &this->mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * numberOfIndices, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	this->mNumberOfIndices = numberOfIndices;

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	delete[] indices;
	delete[] vertices;
}

Model::Model() {}

Model::~Model()
{


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//glDeleteBuffers(1, &mVBO);
	//glDeleteBuffers(1, &mIBO);
}
void Model::Init()
{
	FILE* file = fopen(modelFile, "rb");
	if (file != NULL)
	{
		printf("\nfile Model is: %s", modelFile);
		bool result = InitNFG(file);
		fclose(file);
	}
	else {
		printf("\nfail to open file model: %s", modelFile);
	}
}
void Model::Draw() {
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glDrawElements(GL_TRIANGLES, mNumberOfIndices, GL_UNSIGNED_INT, 0);
}