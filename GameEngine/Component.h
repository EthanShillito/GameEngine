#ifndef component_h
#define component_h
#include "Transform.h"

class Component
{
private:
	Transform parentTransform;

protected:
	Transform localTransform;
public:
	virtual void SetParentTransform(Transform parentTransform);

	Transform GetWorldTransform();
};

#endif


