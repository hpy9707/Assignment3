#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"
class Bullet :public GameObject {
private:
	CBoundingBox m_boundingBox;

	float m_speed;
	float m_damage;

	Vector3 m_forward;

	float m_lifetime;
	bool m_alive;

public:
	Bullet(Mesh* mesh, Shader* shader, Texture* texture, float damage, Vector3 position, Vector3 forward);

	void Update(float timestep);
	void Render(Direct3D* renderer, Camera* cam);

	void OnEnemyCollisionEnter();
	void OnPlayerCollisionEnter();

	bool getBulletalive() { return m_alive; }
	CBoundingBox GetBounds() { return m_boundingBox; }
};





#endif