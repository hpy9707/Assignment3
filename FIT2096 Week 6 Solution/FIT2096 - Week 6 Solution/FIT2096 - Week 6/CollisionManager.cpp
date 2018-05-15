//#include "CollisionManager.h"
//
//CollisionManager::CollisionManager(std::vector<Player*>* players, std::vector<Enemy*>* enemy, std::vector<HealthPack*>* healthpack)
//{
//	m_player = players;
//	m_enemies = enemy;
//	m_healthPack = healthpack;
//
//	// Clear our arrays to 0 (NULL)
//	memset(m_currentCollisions, 0, sizeof(m_currentCollisions));
//	memset(m_previousCollisions, 0, sizeof(m_previousCollisions));
//
//	m_nextCurrentCollisionSlot = 0;
//}
//
//void CollisionManager::CheckCollisions()
//{
//	
//	PlayerToEnemy();
//	PlayerToHealthPack();
//
//	// Move all current collisions into previous
//	memcpy(m_previousCollisions, m_currentCollisions, sizeof(m_currentCollisions));
//
//	// Clear out current collisions
//	memset(m_currentCollisions, 0, sizeof(m_currentCollisions));
//
//	// Now current collisions is empty, we'll start adding from the start again
//	m_nextCurrentCollisionSlot = 0;
//}
//
//bool CollisionManager::ArrayContainsCollision(GameObject* arrayToSearch[], GameObject* first, GameObject* second)
//{
//	// See if these two GameObjects appear one after the other in specified collisions array
//	// Stop one before length so we don't overrun as we'll be checking two elements per iteration
//	for (int i = 0; i < MAX_ALLOWED_COLLISIONS - 1; i += 2)
//	{
//		if ((arrayToSearch[i] == first && arrayToSearch[i + 1] == second) ||
//			arrayToSearch[i] == second && arrayToSearch[i + 1] == first)
//		{
//			// Found them!
//			return true;
//		}
//	}
//
//	// These objects were not colliding last frame
//	return false;
//}
//
//void CollisionManager::AddCollision(GameObject* first, GameObject* second)
//{
//	// Add the two colliding objects to the current collisions array
//	// We keep track of the next free slot so no searching is required
//	m_currentCollisions[m_nextCurrentCollisionSlot] = first;
//	m_currentCollisions[m_nextCurrentCollisionSlot + 1] = second;
//
//	m_nextCurrentCollisionSlot += 2;
//}
//
//void CollisionManager::PlayerToEnemy() {
//	for (unsigned int i = 0; i < m_player->size(); i++) {
//		for (unsigned int j = 0; j < m_enemies->size(); j++) {
//			Player* player = (*m_player)[i];
//			Enemy* enemy = (*m_enemies)[j];
//
//			CBoundingBox playerBounds = player->GetBounds();
//			CBoundingBox enemyBounds = enemy->GetBounds();
//
//			bool isColliding = CheckCollision(playerBounds, enemyBounds);
//			bool wasColliding = ArrayContainsCollision(m_previousCollisions, player, enemy);
//			
//
//			if (isColliding) {
//				AddCollision(player, enemy);
//
//				if (wasColliding) {
//					player->OnEnemyCollisionStay(enemy);
//				}
//				else {
//					player->OnEnemyCollisionEnter(enemy);
//				}
//			}
//			else {
//				if (wasColliding) {
//					player->OnEnemyCollisionExit(enemy);
//				}
//			}
//		}
//	}
//}
//
//void CollisionManager::PlayerToHealthPack() {
//
//}