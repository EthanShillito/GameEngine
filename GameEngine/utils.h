#ifndef utils_h
#define utils_h
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "stb_image.h"

namespace Util {

	unsigned int loadTexture(const char* path);
}

#endif