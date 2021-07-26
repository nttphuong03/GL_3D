#include "stdafx.h"
#include "Object.h"
#include "Vertex.h"

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
void Object::Draw(Camera camera) {
	
	glUseProgram(shaderObj.program);
	for (int j = 0; j < textureNum; j++) {
			glBindTexture(GL_TEXTURE_2D, texturesObj.at(j).mTextureId);

		}
	glBindBuffer(GL_ARRAY_BUFFER, modelObj.mVBO);
	if (shaderObj.positionAttribute != -1)
	{
		glEnableVertexAttribArray(shaderObj.positionAttribute);
		glVertexAttribPointer(shaderObj.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	if (shaderObj.uvAttribute != -1)
	{
		glEnableVertexAttribArray(shaderObj.uvAttribute);
		glVertexAttribPointer(shaderObj.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(Vector3)));
	}
	glUniformMatrix4fv(shaderObj.u_Model, 1, GL_FALSE, *this->GetModelMatrix().m);
	glUniformMatrix4fv(shaderObj.u_Projection, 1, GL_FALSE, *camera.GetPerspectiveMatrix().m);
	glUniformMatrix4fv(shaderObj.u_View, 1, GL_FALSE, *camera.GetViewMatrix().m);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelObj.mIBO);
	glDrawElements(GL_TRIANGLES, modelObj.mNumberOfIndices, GL_UNSIGNED_INT, 0);
}
void Object::Init() {
	int status = shaderObj.Init(shaderObj.fileVS, shaderObj.fileFS);
	modelObj.Init();
	
	for (int i = 0; i < textureNum; i++) {
		texturesObj[i].Init();
		texturesObj[i].shader = shaderObj;
		texturesObj[i].SetUniformLocation("u_texture");
	
	}
	
}

void Object::CleanUp() {
	for (int j = 0; j < textureNum; j++) {
		glDeleteTextures(1, &texturesObj[j].mTextureId);
	}
	shaderObj.~Shaders();
	modelObj.~Model();
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