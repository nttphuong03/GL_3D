#include "stdafx.h"
#include "Light.h"

Light::Light(char* type, Vector3 pos_dir, Vector3 color) {
	this->type = type;
	this->pos_dir = pos_dir;
	this->color = color;
}

Light::Light(){}