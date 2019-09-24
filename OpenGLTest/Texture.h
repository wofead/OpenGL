#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include<filesystem>

#include <string>
#include <iostream>
#include "Shader.h"

#include <std/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



class Texture
{
private:
	unsigned char* data;
	unsigned char* anotherData;
	int width, height, nrChannels;
	unsigned int texture1, texture2, TexVAO, TexVBO, TexEBO;
	glm::mat4 trans;
	Shader ourShader;
	void generateTexture(unsigned int texture, unsigned char* data);
	void setVertex();
	void setShader();
	void setTransform();
	void set3D();
public:
	Texture(std::string texturePath);
	void setAnotherTexture(std::string texturePath);
	void useTexture();
	void useTwoTexture(float mixValue);
	~Texture();
};

