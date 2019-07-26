#include "VertexShader.h"
#include <glad/glad.h>
#include <iostream>
//顶点着色器主要的目的是把3D坐标转为另一种3D坐标（后面会解释），同时顶点着色器允许我们对顶点属性进行一些基本处理。
//#version 330 core    表示OpenGl3.3版本
//layout(location = 0) in vec3 aPos;   //in关键字，在顶点着色器中声明所有的输入顶点属性(Input Vertex Attribute)
//
//void main()
//{
//vec.x、vec.y、vec.z和vec.w,vec.w分量不是用作表达空间中的位置的（我们处理的是3D不是4D），而是用在所谓透视除法(Perspective Division)上
//	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
//}

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec4 vertexColor;;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
"}\0";

unsigned int vertexShader;

VertexShader::VertexShader()
{
	initVertex();
}

void VertexShader::initVertex()
{
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}


unsigned int VertexShader::getVertexShader()
{
	return vertexShader;
}


VertexShader::~VertexShader()
{
	glDeleteShader(vertexShader);
}
