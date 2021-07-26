#pragma once
#include "../Utilities/utilities.h"
#include <cstdio>
#include <GLES2/gl2.h>
#include "Object.h"

class Lighting:public Object
{
public:
	float ambient_weight;
	float spec_power;
	Lighting();
	~Lighting();

	void Draw();
	void Print();
	void Init();

};

