#ifndef gameObject_h
#define gameObject_h
#include "Model.h";
#include "Transform.h"

class GameObject
{
	Model* getModels();

	Transform getWorldTransform();
};
#endif