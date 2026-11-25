#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "Renderer.h"

//callbacks

//temp helper functions
void processInput(GLFWwindow* window);

//window settings
unsigned int SCR_WIDTH;
unsigned int SCR_HEIGHT;

int main() {
	//glfw intialise
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

	//create window
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	SCR_WIDTH = mode->width;
	SCR_HEIGHT = mode->height;
	//GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Engine", glfwGetPrimaryMonitor(), NULL);
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Engine", NULL, NULL);
	if (window == NULL) {
		std::cerr << "ERROR::Failed_To_Create_GLFWwindow" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	//set callbacks

	
	//intialise glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "ERROR::Failed_To_Initalise_Glad" << std::endl;
		glfwTerminate();
		return -1;
	}

	//render setup
	setupRender();

	//Loop
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		renderIteraton();

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}