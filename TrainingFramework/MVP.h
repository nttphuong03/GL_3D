
#pragma once
#include "../Utilities/utilities.h"
#include <cstdio>
#include <GLES2/gl2.h>
#include "Shaders.h"

class MVP
{
public:
	Shaders shader;
	Matrix Rx, Ry, Rz;
	Matrix scaleM;
	Matrix translateM;
	
	MVP(Shaders sharder);
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);
	void Scale(float scaleX, float scaleY, float scaleZ );
	void Translate(Vector3 transVector);
	void Transform(Matrix view, Matrix projection);
	void Transform(Matrix model, Matrix view, Matrix projection);
	~MVP();
};