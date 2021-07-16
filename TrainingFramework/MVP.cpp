#include "stdafx.h"

#include <string.h>
#include <conio.h>
#include "MVP.h"

MVP::MVP(Shaders shader) {
	this->shader = shader;
	Rx.SetIdentity();
	Ry.SetIdentity();
	Rz.SetIdentity();
	scaleM.SetIdentity();
	translateM.SetIdentity();
}

void MVP::RotateX(float angleDegree) {
	Rx.SetRotationX(angleDegree /180 * 3.14);
}

void MVP::RotateY(float angleDegree) {
	Ry.SetRotationY(angleDegree / 180 * 3.14);
}

void MVP::RotateZ(float angleDegree) {
	Rz.SetRotationZ(angleDegree / 180 * 3.14);
}

void MVP::Scale(GLfloat scaleX, float scaleY, float scaleZ) {
	scaleM.m[0][0] = scaleX;
	scaleM.m[1][1] = scaleY;
	scaleM.m[2][2] = scaleZ;
}

void MVP::Translate(Vector3 transVector) {
	translateM.SetTranslation(transVector);
}

void MVP::Transform() {
	Matrix rotation = Rz * Ry * Rx;
	Matrix world = scaleM * rotation * translateM;
	GLint tranformLoc = glGetUniformLocation(shader.program, "u_MVP");
	glUniformMatrix4fv(tranformLoc, 1, GL_FALSE, *world.m);
}

MVP::~MVP() {

}