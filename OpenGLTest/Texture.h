#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include<filesystem>

#include <string>
#include <iostream>
#include "Shader.h"

#include <std/stb_image.h>

class Texture
{
private:
	unsigned char* data;
	unsigned char* anotherData;
	int width, height, nrChannels;
	unsigned int texture1, texture2, TexVAO, TexVBO, TexEBO;
	Shader ourShader;
	void generateTexture(unsigned int texture, unsigned char* data);
	void setVertex();
	void setShader();
public:
	Texture(std::string texturePath);
	void setAnotherTexture(std::string texturePath);
	void useTexture();
	void useTwoTexture(float mixValue);
	~Texture();
};

