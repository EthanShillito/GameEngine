#ifndef transform_h
#define transform_h

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Transform
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Transform(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 rot = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f)) {
		position = pos;
		rotation = rot;
		this->scale = scale;
	}

	Transform operator +(const Transform& other) {
		return Transform(this->position + other.position, this->rotation + other.rotation, this->scale + other.scale); //I think actually needs to be matrix multiplication but works for now
	}

	void operator +=(const Transform& other) {
		*this = *this + other;
	}
};
#endif