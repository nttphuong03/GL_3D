#pragma once
#include "../Utilities/utilities.h"
#include <cstdio>
#include <GLES2/gl2.h>
#include "Object.h"

class Mapping :public Object
{
public:
	float ambient_weight;
	float spec_power;
	Mapping();
	~Mapping();

	void Draw();
	void Print();

};

