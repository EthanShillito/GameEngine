#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader() {}

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	//Read shader code from file
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vertexStream;
	std::ifstream fragmentStream;

	vertexStream.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	fragmentStream.exceptions(std::ifstream::badbit | std::ifstream::failbit);

	try {
		vertexStream.open(vertexPath);
		fragmentStream.open(fragmentPath);
		std::stringstream vertexString, fragmentString;
		vertexString << vertexStream.rdbuf();
		fragmentString << fragmentStream.rdbuf();
		vertexStream.close();
		fragmentStream.close();
		vertexCode = vertexString.str();
		fragmentCode = fragmentString.str();

	}
	catch (std::ifstream::failure e) {
		std::cerr << "ERROR::SHADER::File_Not_Read: " << e.what() << std::endl;
	}

	const char* vertexShaderSource = vertexCode.c_str();
	const char* fragmentShaderSource = fragmentCode.c_str();

	//Compile shaders
	unsigned int vertexShader, fragmentShader;
	int success;
	char infoLog[512];

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX_SHADER::COMPILE_FAIL\n" << infoLog << std::endl;
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT_SHADER::COMPILE_FAIL\n" << infoLog << std::endl;
	}

	//Create shader program
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINK_FAIL\n" << infoLog << std::endl;
	}

	//Remove shaders now in program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
void Shader::Use() {
	glUseProgram(ID);
}

//Uniforms
void Shader::setBool(const std::string& name, bool value) {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, glm::vec2 value) {
	glUniform2f(glGetUniformLocation(ID, name.c_str()), value.x, value.y);
}

void Shader::setVec2(const std::string& name, float x, float y) {
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string& name, glm::vec3 value) {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setMat4(const std::string& name, const glm::mat4& value) {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}