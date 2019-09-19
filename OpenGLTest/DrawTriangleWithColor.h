#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class DrawTriangleWithColor
{
private:
	
	unsigned int VBO, VAO;
	void initVAOAndVBO();
public:
	DrawTriangleWithColor();
	void drawTriangle();
	~DrawTriangleWithColor();
};

