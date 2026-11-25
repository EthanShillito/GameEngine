#ifndef utils_h
#define utils_h
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "stb_image.h"

unsigned int loadTexture(const char* path) {
	unsigned int texutreID;
	glGenTextures(1, &texutreID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);

	if (data) {
		GLenum format;
		if (nrComponents == 1) { format = GL_RED; }
		else if (nrComponents == 3) { format = GL_RGB; }
		else if (nrComponents == 4) { format = GL_RGBA; }

		glBindTexture(GL_TEXTURE_2D, texutreID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	{
		std::cerr << "ERROR::Texture_Failed_To_Load_At_Path: " << path << std::endl;
		stbi_image_free(data);
	}

	return texutreID;
}

#endif