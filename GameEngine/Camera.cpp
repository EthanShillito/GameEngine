#include "Camera.h"
#include <iostream>

//Note x = roll, y = pitch, z = yaw

//constructor
Camera::Camera(Transform localTransform, float fov, glm::vec3 worldUp, float min, float max) {
	this->localTransform = localTransform;
	this->fov = fov;
	this->WorldUp = worldUp;
	this->minDraw = min;
	this->maxDraw = max;
	UpdateCameraVectors();
}

//Get matrix to transform from world space to camera view space
glm::mat4 Camera::GetViewMatrix() {
	Transform worldTransform = GetWorldTransform();
	return glm::lookAt(worldTransform.position, worldTransform.position + Front, Up);
}

//Get matrix to transform from view space to projected space
glm::mat4 Camera::GetPerspectiveMatrix(float aspectRatio) {
	return glm::perspective(glm::radians(fov), aspectRatio, minDraw, maxDraw);
}

//When transform is changed update vectors
void Camera::SetParentTransform(Transform parentTransform) {
	Component::SetParentTransform(parentTransform);
	UpdateCameraVectors();
}

//Upadte vectors used for matrix caluclation to match current transform
void Camera::UpdateCameraVectors() {
	Transform worldTransform = GetWorldTransform();
	//Calc front vector
	glm::vec3 front;
	front.x = cos(glm::radians(worldTransform.rotation.z)) * cos(glm::radians(worldTransform.rotation.y));
	front.y = sin(glm::radians(worldTransform.rotation.y));
	front.z = sin(glm::radians(worldTransform.rotation.z)) * cos(glm::radians(worldTransform.rotation.y));
	Front = glm::normalize(front);

	//Calc up and down from this - need to rotate from roll still
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}