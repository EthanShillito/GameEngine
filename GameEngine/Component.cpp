#include "Component.h"

void Component::SetParentTransform(Transform parentTransform) {
	this->parentTransform = parentTransform;
}

Transform Component::GetWorldTransform() {
	return parentTransform + localTransform;
}