#include "Camera.h"
#include <iostream>

//Note x = roll, y = pitch, z = yaw

//constructor
Camera::Camera(Transform transform, float fov, glm::vec3 worldUp, float min, float max) {
	this->transform = transform;
	this->fov = fov;
	this->WorldUp = worldUp;
	this->minDraw = min;
	this->maxDraw = max;
	UpdateCameraVectors();
}

//Get matrix to transform from world space to camera view space
glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(transform.position, transform.position + Front, Up);
}

//Get matrix to transform from view space to projected space
glm::mat4 Camera::GetPerspectiveMatrix(float aspectRatio) {
	return glm::perspective(glm::radians(fov), aspectRatio, minDraw, maxDraw);
}

//Add transformation change
void Camera::ApplyTransform(Transform delta) {
	transform += delta;
	UpdateCameraVectors();
}

//Upadte vectors used for matrix caluclation to match current transform
void Camera::UpdateCameraVectors() {
	//Calc front vector
	glm::vec3 front;
	front.x = cos(glm::radians(transform.rotation.z)) * cos(glm::radians(transform.rotation.y));
	front.y = sin(glm::radians(transform.rotation.y));
	front.z = sin(glm::radians(transform.rotation.z)) * cos(glm::radians(transform.rotation.y));
	Front = glm::normalize(front);

	//Calc up and down from this - need to rotate from roll still
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}