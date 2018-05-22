/*	FIT2096 - Assignment 1 Sample Solution
*	Player.h
*	Created by Mike Yeates - 2017 - Monash University
*	A Player listens to the keyboard and responds to arrow key presses.
*	It LERPs itself between cells and also asks the GameBoard where it can move.
*/

#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "InputController.h"
#include "GameBoard.h"
#include"Gun.h"


class Player : public GameObject
{
private:
	// A Player should listen for its own input
	InputController* m_input;

	// We'll be animating our movement so a second position is required
	//Vector3 m_targetPosition;
	float m_moveSpeed;

	// Which board is the player currently on
	GameBoard* m_currentBoard;

	CBoundingBox m_boundingBox;


	// Game variables
	float m_health;
	int m_score;
	int m_monstersDefeated;
	//bool m_isTrapped;
	bool teleporting;
	float m_heading;
	float m_pitch;
	float m_rotationSpeed;
	//Monster* m_monster;
	// Ask the GameBoard if we are allowed to move to a particular tile
	bool CanMoveHere(Vector3 target);
	void resetpos(Vector3 target_pos);
	Gun* m_gun;
	void TeleportToTileOfType(TileType type);
	Vector3 m_facingposition;
	
	

public:
	Player();
	Player(Mesh* mesh, Shader* shader, Texture* texture, InputController* input, GameBoard* board, BulletManager* bulletmanager);
	~Player();
	void addScore(int num) { m_score += num; m_monstersDefeated++; }
	void Update(float timestep);
	void OnHealingCollisionEnter();
	void OnBulletCollisionEnter();
	void OnTileCollisionEnter();
	void OnTileCollisionExit();
	float GetHealth() { return m_health; }
	Vector3 GetFacingpos() { return  m_facingposition; }

	
	int GetNumberOfMonstersDefeated() { return m_monstersDefeated; }
	int GetScore() { return m_score; }
	int GetPlayerClip();
	int GetPlayerMagazine();
	bool getreload() { return m_gun->getreload(); }
	bool getTeleport() { return teleporting; }
	CBoundingBox GetBounds() { return m_boundingBox; }
	
};

#endif
