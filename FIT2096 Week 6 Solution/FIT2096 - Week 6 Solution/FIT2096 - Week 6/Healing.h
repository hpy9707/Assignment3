#ifndef HEALING_H
#define HEALING_H

#include "GameObject.h"

// This really doesn't do much at all. Because GameObject is abstract we need something to represent
// objects which basically sit there doing nothing. You could ditch this class and just use GameObject
// directly if you strip out the abstract stuff. We kept it in as an excuse to write an abstract class.

class Healing : public GameObject
{
public:
	Healing() : GameObject() {}
	Healing(Mesh* mesh, Shader* shader) : GameObject(mesh, shader) {}
	Healing(Mesh* mesh, Shader* shader, Texture* texture) : GameObject(mesh, shader, texture) {}
	Healing(Mesh* mesh, Shader* shader, Vector3 position) : GameObject(mesh, shader, position) {}
	Healing(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position) : GameObject(mesh, shader, texture, position) {}

	void Update(float timestep)
	{
		// Update does nothing for a static object
		// We need to provide an implementation though otherwise we will become abstract
		// (not worth moving this out into a seperate cpp file)
	}
};

#endif