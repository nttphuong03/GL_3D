
#include "stdafx.h"
#include "Shaders.h"

int Shaders::Init(char* fileVertexShader, char* fileFragmentShader)
{
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if (vertexShader == 0)
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	//finding location of uniforms / attributes
	positionAttribute = glGetAttribLocation(program, "a_posL");
	colorAttribute = glGetAttribLocation(program, "a_color");
	uvAttribute = glGetAttribLocation(program, "a_uv");
	transform = glGetUniformLocation(program, "MVP");

	u_Model = glGetUniformLocation(program, "u_Model");
	u_View = glGetUniformLocation(program, "u_View");
	u_Projection = glGetUniformLocation(program, "u_Projection");
	return 0;
}
int Shaders::Init()
{
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVS);

	if (vertexShader == 0)
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFS);

	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	if (depth_test) {
		glEnable(GL_DEPTH_TEST);
	}
	if (cull_face) {
		glEnable(GL_CULL_FACE);
	}
	//finding location of uniforms / attributes
	positionAttribute = glGetAttribLocation(program, "a_posL");
	colorAttribute = glGetAttribLocation(program, "a_color");
	uvAttribute = glGetAttribLocation(program, "a_uv");
	transform = glGetUniformLocation(program, "MVP");

	u_Model = glGetUniformLocation(program, "u_Model");
	u_View = glGetUniformLocation(program, "u_View");
	u_Projection = glGetUniformLocation(program, "u_Projection");
	return 0;
}


Shaders::~Shaders()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}