#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include "Draw.h"

//glfwGLFW是一个专门针对OpenGL的C语言库，它提供了一些渲染物体所需的最低限度的接口
//因为OpenGL只是一个标准/规范，具体的实现是由驱动开发商针对特定显卡实现的。由于OpenGL驱动版本众多，它大多数函数的位置都无法在编译时确定下来，需要在运行时查询。
//但是glad库可以准确的找到OpenGL函数

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int flag = 1;
void processInput(GLFWwindow* window)
{
	//监听esc键
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	//监听tab键
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
	glfwInit();// 初始化glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//配置glfw，第一个参数表示选项的名称，第二个参数设置这个选项的值，主版本号3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//次版本号3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//告诉glfw使用的是核心模式
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);//窗口对象，这个窗口存放了所有和窗口相关的数据，宽高和窗口的标题
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//glad是用来管理OpenGL的函数指针的，所以在调用任何OpenGL函数之前我们需要初始化GLAD，我们给glad传入用来加载系统相关的OpenGL函数指针地址的函数，
	//glfw给我们的是glfwGetProcAddress
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

	//渲染之前我们还要告诉OpenGL渲染窗口的大小，即视口，这样OpenGL才知道怎么根据窗口大小显示数据和坐标

	glViewport(0, 0, 800, 600);
	//窗口大小发生改变的时候，视口大小也应该发生变化
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//我们不能渲染一次就退出，所有我们希望窗口在我们没有主动关闭它之前，它可以一直渲染，所以有一个循环渲染。
	while (!glfwWindowShouldClose(window)) //函数在我们每次循环的开始前检查一次GLFW是否被要求退出
	{
		//输入
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//glClearColor来设置清空屏幕所用的颜色
		glClear(GL_COLOR_BUFFER_BIT);//glClear函数来清空屏幕的颜色缓冲，它接受一个缓冲位(Buffer Bit)来指定要清空的缓冲，可能的缓冲位有
		//GL_COLOR_BUFFER_BIT，GL_DEPTH_BUFFER_BIT和GL_STENCIL_BUFFER_BIT。
		if (flag == 1)
		{
			glUseProgram(shaderProgram1);
			draw.toDrawTriangle(1);
		}
		else {
			glUseProgram(shaderProgram);
			draw.toDrawTriangle(2);
		}

		glfwSwapBuffers(window);//函数会交换颜色缓冲,它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上
		glfwPollEvents();//监听出发时间，更新窗口状态，并调用对应的回调函数
	}
	//双缓冲：应用程序使用单缓冲绘图时可能会存在图像闪烁的问题。 这是因为生成的图像不是一下子被绘制出来的，而是按照从左到右，由上而下逐像素地绘制而成的。
	//最终图像不是在瞬间显示给用户，而是通过一步一步生成的，这会导致渲染的结果很不真实。为了规避这些问题，我们应用双缓冲渲染窗口应用程序。
	//前缓冲保存着最终输出的图像，它会在屏幕上显示；而所有的的渲染指令都会在后缓冲上绘制。
	//当所有的渲染指令执行完毕后，我们交换(Swap)前缓冲和后缓冲，这样图像就立即呈显出来，之前提到的不真实感就消除了。

	glfwTerminate();//释放/删除之前的分配的所有资源

	return 0;
}