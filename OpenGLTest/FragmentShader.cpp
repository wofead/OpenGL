#include "FragmentShader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
//Ƭ����ɫ������ҪĿ���Ǽ���һ�����ص�������ɫ����Ҳ������OpenGL�߼�Ч�������ĵط���ͨ����Ƭ����ɫ������3D���������ݣ�������ա���Ӱ�������ɫ�ȵȣ���
//��Щ���ݿ��Ա����������������ص���ɫ��
//��ɫ����ɫ����ɫ��alpha(͸����)������ͨ����дΪRGBA��
//��OpenGL��GLSL�ж���һ����ɫ��ʱ�����ǰ���ɫÿ��������ǿ��������0.0��1.0֮�䡣

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor;\n"
"void main()\n"
"{\n"
"   FragColor = vertexColor;\n"
"}\n\0";

const char* fragmentShaderSource1 = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}\n\0";


unsigned int fragmentShader;
unsigned int fragmentShader1;

FragmentShader::FragmentShader()
{
	initFragment();
}

void FragmentShader::initFragment()
{
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	int success;
	char infoLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
	glCompileShader(fragmentShader1);
	glGetShaderiv(fragmentShader1, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader1, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}


unsigned int FragmentShader::getFragmentShader(int type)
{
	if (type == 1)
	{
		return fragmentShader1;
	}
	return fragmentShader;
}


FragmentShader::~FragmentShader()
{
	glDeleteShader(fragmentShader);
}
