#include "Texture.h"
float verticesTex[] = {
	//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
};

unsigned int indicesTex[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
};

void Texture::generateTexture(unsigned int texture, unsigned char* data)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
}

void Texture::setVertex()
{
	glGenVertexArrays(1, &TexVAO);
	glGenBuffers(1, &TexVBO);
	glGenBuffers(1, &TexEBO);
	glBindVertexArray(TexVAO);

	glBindBuffer(GL_ARRAY_BUFFER, TexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTex), verticesTex, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, TexEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesTex), indicesTex, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

void Texture::setShader()
{
	ourShader = Shader("shader/VertexShaderTex.vs", "shader/FragMentShaderTwoTex.fs");
}

Texture::Texture(std::string texturePath)
{
	//设置VAO，VBO以及纹理指针位置
	setVertex();
	setShader();
	// 加载并生成纹理
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture:" << texturePath << std::endl;
	}
	stbi_image_free(data);
}

void Texture::setAnotherTexture(std::string texturePath)
{
	// 加载并生成纹理
	anotherData = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
	if (anotherData)
	{
		glGenTextures(1, &texture2);
		glBindTexture(GL_TEXTURE_2D, texture2);
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, anotherData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture:" << texturePath << std::endl;
	}
	stbi_image_free(anotherData);
	ourShader.use();
	ourShader.setInt("texture1", 0); // 或者使用着色器类设置
	ourShader.setInt("texture2", 1); // 或者使用着色器类设置
	
}

void Texture::useTexture()
{
	//glBindTexture(GL_TEXTURE_2D, texture);
	ourShader.use();
	//glBindVertexArray(TexVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Texture::useTwoTexture(float mixValue)
{
	//glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	ourShader.setFloat("mixValue", mixValue);
	ourShader.use();
	glBindVertexArray(TexVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Texture::~Texture()
{
	glDeleteVertexArrays(1, &TexVAO);
	glDeleteBuffers(1, &TexVBO);
	glDeleteBuffers(1, &TexEBO);
}
