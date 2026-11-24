#ifndef gameObject_h
#define gameObject_h
#include "Model.h";

class GameObject
{
	Model* getModels();

	Transform getWorldTransform();
};
#endif