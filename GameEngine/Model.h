#ifndef model_h
#define model_h
#include "Transform.h";
#include "Mesh.h";
class Model
{
	void Draw(Shader* shader, Transform transform);
};
#endif