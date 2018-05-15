#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include<vector>
#include"Collisions.h"
#include"Player.h"
#include"Testing.h"
#include"StaticObject.h"
#include"Bullet.h"

#define MAX_ALLOWED_COLLISIONS 2048

class CollisionManager {
private:
	std::vector<Player*>* m_player;
	std::vector<Monster*>* m_enemies;
	std::vector<StaticObject*>* m_healthPack;
	std::vector<Bullet*>* m_bullets;

	GameObject* m_currentCollisions[MAX_ALLOWED_COLLISIONS];
	GameObject* m_previousCollisions[MAX_ALLOWED_COLLISIONS];

	int m_nextCurrentCollisionSlot;
	bool ArrayContainsCollision(GameObject* arrayToSearch[], GameObject* first, GameObject* second);
	void AddCollision(GameObject* first, GameObject* second);

	void PlayerToEnemy();
	void PlayerToHealthPack();
	void BulletToPlayer();
	void BulletToEnemy();

public:
	CollisionManager(std::vector<Player*>* players, std::vector<Monster*>* enemy, std::vector<StaticObject*>* healthpack);
	void CheckCollisions();
};






#endif // !COLLISION_MANAGER_H
