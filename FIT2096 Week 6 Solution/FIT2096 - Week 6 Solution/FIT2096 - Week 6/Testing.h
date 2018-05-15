#ifndef TESTING_H
#define TESTING_H
#include "GameObject.h"
#include "MathsHelper.h"
#include "math.h"

class Monster : public GameObject
{
private:
	int m_health;
	int m_skill;
	bool m_isAlive;
public:

	Monster() : GameObject() {}
	Monster(Mesh* mesh, Shader* shader) : GameObject(mesh, shader) {}
	Monster(Mesh* mesh, Shader* shader, Texture* texture) : GameObject(mesh, shader, texture) {}
	Monster(Mesh* mesh, Shader* shader, Vector3 position) : GameObject(mesh, shader, position) {}
	Monster(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position) : GameObject(mesh, shader, texture, position) {}
	void LookAt(Vector3 Target);
	void Update(float timestep);
	int Attack();
	void BeHit(int amount);

	void rest();
	bool IsAlive() { return m_isAlive; }
	int GetSkill() { return m_skill; }
	

	
};
#endif
