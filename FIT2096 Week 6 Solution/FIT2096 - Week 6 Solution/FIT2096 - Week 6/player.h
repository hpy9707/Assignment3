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
#include"monster.h"

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

	


	// Game variables
	float m_health;
	int m_score;
	int m_monstersDefeated;
	//bool m_isTrapped;
	
	float m_heading;
	
	float m_rotationSpeed;
	//Monster* m_monster;
	// Ask the GameBoard if we are allowed to move to a particular tile
	bool CanMoveHere(Vector3 target);
	void resetpos(Vector3 target_pos);
	// Check if surrounding cells are walkable
	//void CheckIfTrapped();

	// Housekeeping after we receive input
	//void FinishTurn();

	// Check what type of tile is beneth us and react
	//void ReactToTile();

	// Used to spawn the player in a random position and teleport between blue tiles
	void TeleportToTileOfType(TileType type);

	// For Monster battles
	//int Attack();
	void BeHit(int amount);
	//void DoMonsterBattle();

public:
	Player();
	Player(Mesh* mesh, Shader* shader, Texture* texture, InputController* input, GameBoard* board);
	~Player();

	void Update(float timestep);

	// The Game class will use these to determine if the game should end
//	bool GetIsTrapped() { return m_isTrapped; }
	float GetHealth() { return m_health; }
	//bool getmonsterAlive() { return m_monster->IsAlive(); }

	// Game will use these to output info to the player
	int GetNumberOfMonstersDefeated() { return m_monstersDefeated; }
	int GetScore() { return m_score; }
	
};

#endif
