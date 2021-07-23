#pragma once
#pragma once
#include "../Utilities/utilities.h"
#include <cstdio>
#include <GLES2/gl2.h>
class Light
{

public:
	char* type;
	Vector3 pos_dir, color;

	Light();
	Light(char* type, Vector3 pos_dir, Vector3 color);
};