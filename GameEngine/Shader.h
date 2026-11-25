#ifndef shader_h
#define shader_h

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	void Use();
	void setBool(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setVec2(const std::string& name, glm::vec2 value);
	void setVec2(const std::string &name, float x, float y);
	void setVec3(const std::string& name, glm::vec3 value);
	void setVec3(const std::string& name, float x, float y, float z);
	void setMat4(const std::string& name, glm::mat4 value);
};
#endif