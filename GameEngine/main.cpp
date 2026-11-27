#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION

#include "Model.h"
#include "Camera.h"

//callbacks
void frameBufferSizeCallback(GLFWwindow* window, int width, int height);

//temp helper functions
void processInput(GLFWwindow* window);

//window settings
unsigned int SCR_WIDTH;
unsigned int SCR_HEIGHT;
bool fullscreen = false;

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
	GLFWwindow* window;
	if (fullscreen) {
		window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Engine", glfwGetPrimaryMonitor(), NULL);
	}
	else {
		window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Engine", NULL, NULL);
	}
	if (window == NULL) {
		std::cerr << "ERROR::Failed_To_Create_GLFWwindow" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	//set callbacks
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

	
	//intialise glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "ERROR::Failed_To_Initalise_Glad" << std::endl;
		glfwTerminate();
		return -1;
	}

	//render setup
	glEnable(GL_DEPTH_TEST);

	//testing
	Shader defaultShader = Shader("Shaders/DefaultShader.vs", "Shaders/DefaultShader.fs");

	std::vector<Model> models;
	models.push_back(Model("Meshes/Box/box.obj"));

	Camera camera = Camera(Transform(glm::vec3(-7.0f, 3.0f, 3.0f), glm::vec3(0.0f, -25.0f, -20.0f)));

	//Loop
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.51f, 0.81f, 0.88f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		defaultShader.Use();
		glm::mat4 projection = camera.GetPerspectiveMatrix(SCR_WIDTH / (float)SCR_HEIGHT);
		glm::mat4 view = camera.GetViewMatrix();

		glm::mat4 model = glm::mat4(1.0f);
		glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

		defaultShader.setMat4("model", model);
		defaultShader.setMat4("view", view);
		defaultShader.setMat4("projection", projection);

		for (int i = 0; i < models.size(); i++) {
			models[i].Draw(defaultShader);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
}