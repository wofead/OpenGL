#include "DrawTriangel.h"
#include <glad/glad.h>

float vertices[] = {
		 0.5f, 0.5f, 0.0f,   // ���Ͻ�
		 0.5f, -0.5f, 0.0f,  // ���½�
		-0.5f, -0.5f, 0.0f, // ���½�
		-0.5f, 0.5f, 0.0f,   // ���Ͻ�   
		 0.0f, 0.0f, 0.0f
};

unsigned int indices[] = { // ע��������0��ʼ! 
	0, 1, 4, // ��һ��������
	2, 3, 4,  // �ڶ���������
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
	//���㻺�����(Vertex Buffer Objects, VBO)��������ڴ棬������GPU�ڴ棨ͨ������Ϊ�Դ棩�д����������
	//OpenGL�кܶ໺��������ͣ����㻺�����Ļ���������GL_ARRAY_BUFFER��
	glGenBuffers(2, VBOs);

	glBindVertexArray(VAOs[0]);
	//OpenGL��������ͬʱ�󶨶�����壬ֻҪ�����ǲ�ͬ�Ļ������͡����ǿ���ʹ��glBindBuffer�������´����Ļ���󶨵�GL_ARRAY_BUFFERĿ����
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	//����һ��������ʹ�õ��κΣ���GL_ARRAY_BUFFERĿ���ϵģ�������ö����������õ�ǰ�󶨵Ļ���(VBO)��
	//Ȼ�����ǿ��Ե���glBufferData�����������֮ǰ����Ķ������ݸ��Ƶ�������ڴ��У�
	//glBufferData��һ��ר���������û���������ݸ��Ƶ���ǰ�󶨻���ĺ���
	//���ĵ�һ��������Ŀ�껺������ͣ����㻺�����ǰ�󶨵�GL_ARRAY_BUFFERĿ���ϡ�
	//�ڶ�������ָ���������ݵĴ�С(���ֽ�Ϊ��λ)
	//����������������ϣ�����͵�ʵ�����ݡ�
	//���ĸ�����ָ��������ϣ���Կ���ι�����������ݡ�
	//1. GL_STATIC_DRAW �����ݲ���򼸺�����ı䡣2. GL_DYNAMIC_DRAW�����ݻᱻ�ı�ܶࡣ3. GL_STREAM_DRAW ������ÿ�λ���ʱ����ı䡣
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
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
	//ͼԪװ��(Primitive Assembly)�׶ν�������ɫ����������ж�����Ϊ���루�����GL_POINTS����ô����һ�����㣩�������еĵ�װ���ָ��ͼԪ����״��
	//GL_POINTS��GL_TRIANGLES��GL_LINE_STRIP
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(VAOs[1]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void DrawTriangel::initTriangleWithEBO()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// 1. �󶨶����������
	glBindVertexArray(VAO);
	// 2. �����ǵĶ������鸴�Ƶ�һ�����㻺���У���OpenGLʹ��
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3. �������ǵ��������鵽һ�����������У���OpenGLʹ��
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 4. �趨��������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


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
