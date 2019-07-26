#include "VertexShader.h"
#include <glad/glad.h>
#include <iostream>
//������ɫ����Ҫ��Ŀ���ǰ�3D����תΪ��һ��3D���꣨�������ͣ���ͬʱ������ɫ���������ǶԶ������Խ���һЩ��������
//#version 330 core    ��ʾOpenGl3.3�汾
//layout(location = 0) in vec3 aPos;   //in�ؼ��֣��ڶ�����ɫ�����������е����붥������(Input Vertex Attribute)
//
//void main()
//{
//vec.x��vec.y��vec.z��vec.w,vec.w���������������ռ��е�λ�õģ����Ǵ������3D����4D��������������ν͸�ӳ���(Perspective Division)��
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
