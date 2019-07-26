#include "Shader.h"
#include <glad/glad.h>
#include <iostream>
#include "VertexShader.h"
#include "FragmentShader.h"


unsigned int shaderProgram;
unsigned int shaderProgram1;
Shader::Shader()
{
	shaderProgram = createShaderProgram(1);
	shaderProgram1 = createShaderProgram(2);
}

unsigned int Shader::createShaderProgram(int type)
{
	VertexShader vertex = VertexShader();
	FragmentShader fragment = FragmentShader();
	unsigned int shader = glCreateProgram();
	glAttachShader(shader, vertex.getVertexShader());
	glAttachShader(shader, fragment.getFragmentShader(type));
	glLinkProgram(shader);
	int success;
	char infoLog[512];
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	return shader;
}

unsigned int Shader::getShaderProgram(int type)
{
	if (type == 1)
	{
		return shaderProgram;
	}
	else {
		return shaderProgram1;
	}
}


Shader::~Shader()
{
}
