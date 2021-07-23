#pragma once
#include "../Utilities/utilities.h"

class Shaders
{
public:
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];
	bool depth_test, cull_face, blend;
	char src_alpha[50], scr_one[200];

	GLint positionAttribute;
	GLint colorAttribute;
	GLint uvAttribute;
	GLint transform;

	GLint u_Model;
	GLint u_View;
	GLint u_Projection;

	int Init(char* fileVertexShader, char* fileFragmentShader);
	int Init();

	~Shaders();
};