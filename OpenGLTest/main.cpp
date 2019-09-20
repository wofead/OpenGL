#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>
//#include "Draw.h"
//#include "Shader.h"
//#include "DrawTriangleWithColor.h"
#include "Texture.h"

//glfwGLFW��һ��ר�����OpenGL��C���Կ⣬���ṩ��һЩ��Ⱦ�������������޶ȵĽӿ�
//��ΪOpenGLֻ��һ����׼/�淶�������ʵ��������������������ض��Կ�ʵ�ֵġ�����OpenGL�����汾�ڶ࣬�������������λ�ö��޷��ڱ���ʱȷ����������Ҫ������ʱ��ѯ��
//����glad�����׼ȷ���ҵ�OpenGL����
float mixValue = 0.2f;
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
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		mixValue += 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
		if (mixValue >= 1.0f)
			mixValue = 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		mixValue -= 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
		if (mixValue <= 0.0f)
			mixValue = 0.0f;
	}
}



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

	

	//Shader shader = Shader();

	//��Ⱦ֮ǰ���ǻ�Ҫ����OpenGL��Ⱦ���ڵĴ�С�����ӿڣ�����OpenGL��֪����ô���ݴ��ڴ�С��ʾ���ݺ�����

	glViewport(0, 0, 800, 600);
	//���ڴ�С�����ı��ʱ���ӿڴ�СҲӦ�÷����仯
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	/*DrawTriangleWithColor drawTriangleWithColor = DrawTriangleWithColor();
	Shader shader("VertexShader.vs","FragMentShader.fs");*/

	Texture tex = Texture("img/container.jpg");
	tex.setAnotherTexture("img/awesomeface.png");

	//���ǲ�����Ⱦһ�ξ��˳�����������ϣ������������û�������ر���֮ǰ��������һֱ��Ⱦ��������һ��ѭ����Ⱦ��
	while (!glfwWindowShouldClose(window)) //����������ÿ��ѭ���Ŀ�ʼǰ���һ��GLFW�Ƿ�Ҫ���˳�
	{
		//����
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//glClearColor�����������Ļ���õ���ɫ
		glClear(GL_COLOR_BUFFER_BIT);//glClear�����������Ļ����ɫ���壬������һ������λ(Buffer Bit)��ָ��Ҫ��յĻ��壬���ܵĻ���λ��
		//GL_COLOR_BUFFER_BIT��GL_DEPTH_BUFFER_BIT��GL_STENCIL_BUFFER_BIT��
		/*if (flag == 1)
		{
			float timeValue = glfwGetTime();
			float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
			int vertexColorLocation = glGetUniformLocation(shader.getShaderProgram(1), "ourColor");
			glUseProgram(shader.getShaderProgram(1));
			glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
			draw.toDrawTriangle(1);
		}
		else {
			glUseProgram(shader.getShaderProgram(2));
			draw.toDrawTriangle(2);
		}*/
		/*shader.use();
		drawTriangleWithColor.drawTriangle();*/
		tex.useTwoTexture(mixValue);
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