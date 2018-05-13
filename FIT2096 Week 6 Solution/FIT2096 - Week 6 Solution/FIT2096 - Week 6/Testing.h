#ifndef TESTING_H
#define TESTING_H
#include "GameObject.h"
#include "MathsHelper.h"
#include "math.h"

class Testing : public GameObject
{
public:

	Testing() : GameObject() {}
	Testing(Mesh* mesh, Shader* shader) : GameObject(mesh, shader) {}
	Testing(Mesh* mesh, Shader* shader, Texture* texture) : GameObject(mesh, shader, texture) {}
	Testing(Mesh* mesh, Shader* shader, Vector3 position) : GameObject(mesh, shader, position) {}
	Testing(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position) : GameObject(mesh, shader, texture, position) {}
	void LookAt(Vector3 Target);
	void Update(float timestep);
	

	
};
#endif
