#pragma once
#include "../Utilities/utilities.h"
#include <cstdio>
#include <GLES2/gl2.h>
#include "Object.h"

class Terrain:public Object
{
public:
	int tiling;
	int fog_start;
	int fog_length;
	Vector3 fog_color;
	Terrain();
	~Terrain();

	void Init();
	void Draw();
	void Print();
private:

};

