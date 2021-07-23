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

void MVP::Transform(Matrix view, Matrix projection) {
	Matrix rotation = Rz * Ry * Rx;
	Matrix world = scaleM * rotation * translateM;
	
	glUniformMatrix4fv(shader.u_Model, 1, GL_FALSE, *world.m);
	glUniformMatrix4fv(shader.u_View, 1, GL_FALSE, *view.m);
	glUniformMatrix4fv(shader.u_Projection, 1, GL_FALSE, *projection.m);
}

void MVP::Transform(Matrix model, Matrix view, Matrix projection) {

	glUniformMatrix4fv(shader.u_Model, 1, GL_FALSE, *model.m);
	glUniformMatrix4fv(shader.u_View, 1, GL_FALSE, *view.m);
	glUniformMatrix4fv(shader.u_Projection, 1, GL_FALSE, *projection.m);
}


MVP::~MVP() {

}