#ifndef camera_h
#define camera_h

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Component.h"

//Camera Defaults
// Default camera values
const Transform TRANSFORM = Transform();
const float FOV = 45.0f;

class Camera : public Component
{
private:
	//Attributes
	float fov;
	glm::vec3 Front;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;
	float minDraw;
	float maxDraw;
	

public:
	Camera(Transform localTransform = TRANSFORM, float fov = FOV, glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f), float min = 0.1f, float max = 100.0f);

	glm::mat4 GetViewMatrix();

	glm::mat4 GetPerspectiveMatrix(float aspectRatio);

	void SetParentTransform(Transform parentTransform) override;

	void UpdateCameraVectors();
};
#endif