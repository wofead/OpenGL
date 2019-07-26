#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include "Draw.h"

//glfwGLFW��һ��ר�����OpenGL��C���Կ⣬���ṩ��һЩ��Ⱦ�������������޶ȵĽӿ�
//��ΪOpenGLֻ��һ����׼/�淶�������ʵ��������������������ض��Կ�ʵ�ֵġ�����OpenGL�����汾�ڶ࣬�������������λ�ö��޷��ڱ���ʱȷ����������Ҫ������ʱ��ѯ��
//����glad�����׼ȷ���ҵ�OpenGL����

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int flag = 1;
void processInput(GLFWwindow* window)
{
	//����esc��
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	//����tab��
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		flag = 2;
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}


//1.0f, 0.5f, 0.2f
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

const char* fragmentShaderSource1 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
"}\n\0";


int main()
{
	glfwInit();// ��ʼ��glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//����glfw����һ��������ʾѡ������ƣ��ڶ��������������ѡ���ֵ�����汾��3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//�ΰ汾��3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//����glfwʹ�õ��Ǻ���ģʽ
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);//���ڶ���������ڴ�������кʹ�����ص����ݣ���ߺʹ��ڵı���
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//glad����������OpenGL�ĺ���ָ��ģ������ڵ����κ�OpenGL����֮ǰ������Ҫ��ʼ��GLAD�����Ǹ�glad������������ϵͳ��ص�OpenGL����ָ���ַ�ĺ�����
	//glfw�����ǵ���glfwGetProcAddress
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int vertexShader1 = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader1, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader1);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// fragment shader1
	int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
	glCompileShader(fragmentShader1);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glGetShaderiv(fragmentShader1, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader1, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT1::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	int shaderProgram1 = glCreateProgram();
	glAttachShader(shaderProgram1, vertexShader1);
	glAttachShader(shaderProgram1, fragmentShader1);
	glLinkProgram(shaderProgram1);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	Draw draw = Draw();

	//��Ⱦ֮ǰ���ǻ�Ҫ����OpenGL��Ⱦ���ڵĴ�С�����ӿڣ�����OpenGL��֪����ô���ݴ��ڴ�С��ʾ���ݺ�����

	glViewport(0, 0, 800, 600);
	//���ڴ�С�����ı��ʱ���ӿڴ�СҲӦ�÷����仯
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//���ǲ�����Ⱦһ�ξ��˳�����������ϣ������������û�������ر���֮ǰ��������һֱ��Ⱦ��������һ��ѭ����Ⱦ��
	while (!glfwWindowShouldClose(window)) //����������ÿ��ѭ���Ŀ�ʼǰ���һ��GLFW�Ƿ�Ҫ���˳�
	{
		//����
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//glClearColor�����������Ļ���õ���ɫ
		glClear(GL_COLOR_BUFFER_BIT);//glClear�����������Ļ����ɫ���壬������һ������λ(Buffer Bit)��ָ��Ҫ��յĻ��壬���ܵĻ���λ��
		//GL_COLOR_BUFFER_BIT��GL_DEPTH_BUFFER_BIT��GL_STENCIL_BUFFER_BIT��
		if (flag == 1)
		{
			glUseProgram(shaderProgram1);
			draw.toDrawTriangle(1);
		}
		else {
			glUseProgram(shaderProgram);
			draw.toDrawTriangle(2);
		}

		glfwSwapBuffers(window);//�����ύ����ɫ����,������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ��
		glfwPollEvents();//��������ʱ�䣬���´���״̬�������ö�Ӧ�Ļص�����
	}
	//˫���壺Ӧ�ó���ʹ�õ������ͼʱ���ܻ����ͼ����˸�����⡣ ������Ϊ���ɵ�ͼ����һ���ӱ����Ƴ����ģ����ǰ��մ����ң����϶��������صػ��ƶ��ɵġ�
	//����ͼ������˲����ʾ���û�������ͨ��һ��һ�����ɵģ���ᵼ����Ⱦ�Ľ���ܲ���ʵ��Ϊ�˹����Щ���⣬����Ӧ��˫������Ⱦ����Ӧ�ó���
	//ǰ���屣�������������ͼ����������Ļ����ʾ�������еĵ���Ⱦָ����ں󻺳��ϻ��ơ�
	//�����е���Ⱦָ��ִ����Ϻ����ǽ���(Swap)ǰ����ͺ󻺳壬����ͼ����������Գ�����֮ǰ�ᵽ�Ĳ���ʵ�о������ˡ�

	glfwTerminate();//�ͷ�/ɾ��֮ǰ�ķ����������Դ

	return 0;
}