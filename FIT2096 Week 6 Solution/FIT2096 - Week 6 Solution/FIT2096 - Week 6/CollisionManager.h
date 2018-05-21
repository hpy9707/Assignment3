#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include<vector>
#include"Collisions.h"
#include"Player.h"
#include"Monster.h"
#include"Healing.h"
#include"Bullet.h"

#define MAX_ALLOWED_COLLISIONS 2048

class CollisionManager {
private:
	std::vector<Player*>* m_player;
	std::vector<Monster*>* m_monsters;
	std::vector<Healing*>* m_healings;
	std::vector<Bullet*>* m_bullets;

	GameObject* m_currentCollisions[MAX_ALLOWED_COLLISIONS];
	GameObject* m_previousCollisions[MAX_ALLOWED_COLLISIONS];

	int m_nextCurrentCollisionSlot;
	bool ArrayContainsCollision(GameObject* arrayToSearch[], GameObject* first, GameObject* second);
	void AddCollision(GameObject* first, GameObject* second);

	
	void PlayerToHealthPack();
	
	void BulletToEnemy();

public:
	CollisionManager(std::vector<Player*>* players, std::vector<Monster*>* enemy, std::vector<Healing*>* healthpack, std::vector<Bullet*>* bullet);
	void CheckCollisions();
};






#endif // !COLLISION_MANAGER_H
