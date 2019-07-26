#include "DrawTriangel.h"
#include <glad/glad.h>

float vertices[] = {
		 0.5f, 0.5f, 0.0f,   // 右上角
		 0.5f, -0.5f, 0.0f,  // 右下角
		-0.5f, -0.5f, 0.0f, // 左下角
		-0.5f, 0.5f, 0.0f,   // 左上角   
		 0.0f, 0.0f, 0.0f
};

unsigned int indices[] = { // 注意索引从0开始! 
	0, 1, 4, // 第一个三角形
	2, 3, 4,  // 第二个三角形
};

float firstTriangle[] = {
	   -0.9f, -0.5f, 0.0f,  // left 
	   -0.0f, -0.5f, 0.0f,  // right
	   -0.45f, 0.5f, 0.0f,  // top 
};

float secondTriangle[] = {
	0.0f, -0.5f, 0.0f,  // left
	0.9f, -0.5f, 0.0f,  // right
	0.45f, 0.5f, 0.0f   // top 
};

unsigned int VBOs[2], VAOs[2];
unsigned int VAO, VBO, EBO;


DrawTriangel::DrawTriangel()
{
	initTriangleWithDifVAO();
	initTriangleWithEBO();
}

void DrawTriangel::initTriangleWithDifVAO()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glGenVertexArrays(2, VAOs);
	//顶点缓冲对象(Vertex Buffer Objects, VBO)管理这个内存，它会在GPU内存（通常被称为显存）中储存大量顶点
	//OpenGL有很多缓冲对象类型，顶点缓冲对象的缓冲类型是GL_ARRAY_BUFFER。
	glGenBuffers(2, VBOs);

	glBindVertexArray(VAOs[0]);
	//OpenGL允许我们同时绑定多个缓冲，只要它们是不同的缓冲类型。我们可以使用glBindBuffer函数把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	//从这一刻起，我们使用的任何（在GL_ARRAY_BUFFER目标上的）缓冲调用都会用来配置当前绑定的缓冲(VBO)。
	//然后我们可以调用glBufferData函数，它会把之前定义的顶点数据复制到缓冲的内存中：
	//glBufferData是一个专门用来把用户定义的数据复制到当前绑定缓冲的函数
	//它的第一个参数是目标缓冲的类型：顶点缓冲对象当前绑定到GL_ARRAY_BUFFER目标上。
	//第二个参数指定传输数据的大小(以字节为单位)
	//第三个参数是我们希望发送的实际数据。
	//第四个参数指定了我们希望显卡如何管理给定的数据。
	//1. GL_STATIC_DRAW ：数据不会或几乎不会改变。2. GL_DYNAMIC_DRAW：数据会被改变很多。3. GL_STREAM_DRAW ：数据每次绘制时都会改变。
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	//顶点属性的位置值;参数指定顶点属性的大小,3个值组成，所以大小是3;参数指定数据的类型;是否希望数据被标准化(Normalize),GL_TRUE，所有数据都会被映射到0（对于有符号型signed数据是-1）到1之间;
	//第五个参数叫做步长(Stride)，它告诉我们在连续的顶点属性组之间的间隔;参数的类型是void*，所以需要我们进行这个奇怪的强制类型转换。它表示位置数据在缓冲中起始位置的偏移量(Offset);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
	//以顶点属性位置值作为参数，启用顶点属性；所以这里的参数是0。
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void DrawTriangel::drawTriangleWithDifVAO()
{
	glBindVertexArray(VAOs[0]);
	//图元装配(Primitive Assembly)阶段将顶点着色器输出的所有顶点作为输入（如果是GL_POINTS，那么就是一个顶点），并所有的点装配成指定图元的形状；
	//GL_POINTS、GL_TRIANGLES、GL_LINE_STRIP
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(VAOs[1]);
	//和索引绘图不同之处
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void DrawTriangel::initTriangleWithEBO()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// 1. 绑定顶点数组对象
	//顶点数组对象(Vertex Array Object, VAO)可以像顶点缓冲对象那样被绑定，任何随后的顶点属性调用都会储存在这个VAO中。这样的好处就是，当配置顶点属性指针时，
	//你只需要将那些调用执行一次，之后再绘制物体的时候只需要绑定相应的VAO就行了。
	//这使在不同顶点数据和属性配置之间切换变得非常简单，只需要绑定不同的VAO就行了。刚刚设置的所有状态都将存储在VAO中
	//一个顶点数组对象会储存以下这些内容：
	//glEnableVertexAttribArray和glDisableVertexAttribArray的调用。
	//通过glVertexAttribPointer设置的顶点属性配置。
	//通过glVertexAttribPointer调用与顶点属性关联的顶点缓冲对象。
	glBindVertexArray(VAO);
	// 2. 把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3. 复制我们的索引数组到一个索引缓冲中，供OpenGL使用.GL_ELEMENT_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 4. 设定顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//。一般当你打算绘制多个物体时，你首先要生成/配置所有的VAO（和必须的VBO及属性指针)，然后储存它们供后面使用。
	//当我们打算绘制物体的时候就拿出相应的VAO，绑定它，绘制完物体后，再解绑VAO。


}

void DrawTriangel::drawTriangleWithEBO()
{
	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


void DrawTriangel::toDrawTriangle(int type)
{
	if (type == 1)
	{
		drawTriangleWithEBO();
	}
	else {
		drawTriangleWithDifVAO();
	}
}


DrawTriangel::~DrawTriangel()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
}
