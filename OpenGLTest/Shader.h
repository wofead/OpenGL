#pragma once
class Shader
{
public:
	Shader();
	unsigned int createShaderProgram(int type);
	unsigned int getShaderProgram(int type);
	~Shader();
};

