#ifndef gameObject_h
#define gameObject_h
#include "Component.h"
#include <vector>

class GameObject
{
private:
	Transform worldTransform;

	std::vector<Component*> components;
public:
	GameObject(Transform transform = Transform(), std::vector<Component*> components = std::vector<Component*>());

	std::vector<Component*> getComponents();

	void attachComponent(Component* component);

	//Transform functions
	Transform getWorldTransform();

	void setWorldTransform(Transform worldTransform);

	void applyWorldTransform(Transform delta);

	void setWorldPosition(glm::vec3 worldPosition);

	void addWorldPosition(glm::vec3 delta);

	void setWorldRotation(glm::vec3 worldRotation);

	void addWorldRotation(glm::vec3 delta);

	void setWorldScale(glm::vec3 worldScale);

	void addWorldScale(glm::vec3 delta);

private:
	void UpdateComponentsTransform();

	void UpdateComponentTransform(Component* component);
};
#endif