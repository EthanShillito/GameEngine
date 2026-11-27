#include "GameObject.h"

GameObject::GameObject(Transform transform, std::vector<Component*> components) {
	this->worldTransform = transform;
	this->components = components;
	UpdateComponentsTransform();
}


std::vector<Component*> GameObject::getComponents() {
	return components;
}

void GameObject::attachComponent(Component* component) {
	components.push_back(component);//TODO - need to make sure not already got a parent
	UpdateComponentTransform(component);
}

Transform GameObject::getWorldTransform() {
	return worldTransform;
}

void GameObject::setWorldTransform(Transform worldTransform) {
	this->worldTransform = worldTransform;
	UpdateComponentsTransform();
}

void GameObject::applyWorldTransform(Transform delta) {
	setWorldTransform(worldTransform + delta);
}

void GameObject::setWorldPosition(glm::vec3 worldPosition) {
	Transform newTransform = Transform(worldTransform);
	newTransform.position = worldPosition;
	setWorldTransform(newTransform);
}

void GameObject::addWorldPosition(glm::vec3 delta) {
	setWorldPosition(worldTransform.position + delta);
}

void GameObject::setWorldRotation(glm::vec3 worldRotation) {
	Transform newTransform = Transform(worldTransform);
	newTransform.rotation = worldRotation;
	setWorldTransform(newTransform);
}

void GameObject::addWorldRotation(glm::vec3 delta) {
	setWorldRotation(worldTransform.rotation + delta);
}

void GameObject::setWorldScale(glm::vec3 worldScale) {
	Transform newTransform = Transform(worldTransform);
	newTransform.scale = worldScale;
	setWorldTransform(newTransform);
}

void GameObject::addWorldScale(glm::vec3 delta) {
	setWorldScale(worldTransform.scale * delta);
}

void GameObject::UpdateComponentsTransform() {
	for (int i = 0; i < components.size(); i++) {
		UpdateComponentTransform(components[i]);
	}
}

void GameObject::UpdateComponentTransform(Component* component) {
	component->SetParentTransform(worldTransform);
}
