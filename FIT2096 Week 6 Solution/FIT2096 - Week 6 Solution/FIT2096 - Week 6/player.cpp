#include "Player.h"

#include "MathsHelper.h"

Player::Player()
{
	m_input = NULL;
	m_moveSpeed = 5.0f;
	m_currentBoard = NULL;
	m_rotationSpeed = 0.75f;
	m_health = 100.0f;
	m_score = 0;
	m_monstersDefeated = 0;
	m_monster = NULL;
}

Player::Player(Mesh* mesh, Shader* shader, Texture* texture, InputController* input, GameBoard* board) : GameObject(mesh, shader, texture, Vector3::Zero)
{
	m_input = input;
	m_moveSpeed = 5.0f;
	m_currentBoard = board;
	m_heading = 0.0f;
	m_rotationSpeed = 0.75f;
	m_health = 100.0f;
	m_score = 0;
	m_monstersDefeated = 0;
	m_monster = new Monster();
	TeleportToTileOfType(TileType::NORMAL);
}

Player::~Player() { delete m_monster;
m_monster = NULL;
}

void Player::Update(float timestep)
{
	// Constantly step towards target position
	// Could add a distance check here, however seeing we only have one player we'll be fine
	m_heading += m_input->GetMouseDeltaX() * m_rotationSpeed * timestep;
	Matrix heading = Matrix::CreateRotationY(m_heading);
	

	// Transform a world right vector from world space into local space
	Vector3 localRight = Vector3::TransformNormal(Vector3(1, 0, 0), heading);

	// Essentially our local forward vector but always parallel with the ground
	// Remember a cross product gives us a vector perpendicular to the two input vectors
	Vector3 localForwardXZ = localRight.Cross(Vector3(0, 1, 0));
	
	
	
	Vector3 right = Vector3::TransformNormal(Vector3(1, 0, 0), heading);

	// Essentially our local forward vector but always parallel with the ground
	// Remember a cross product gives us a vector perpendicular to the two input vectors
	Vector3 forward = localRight.Cross(Vector3(0, 1, 0));

	// We need to identify the frame input was received so we can perform common logic
	// outside of the GetKeyDown IF statements below.
	bool didJustMove = false;
	
	if (m_input->GetKeyHold('W'))
	{
		if (CanMoveHere(m_position + forward))
		{
			// Deactivate tile before we update the target position. This prevents the trail
			// of disabled tiles from getting ahead of the player. It always disables the tile
			// we are leaving as opposed to disabling the one we are moving onto.
			m_position += forward*m_moveSpeed*timestep;
			didJustMove = true;
		}
		else {
			Vector3 target_pos = m_position + forward;
			if (target_pos.x > 15.5) m_position.x = 14.5;
			if (target_pos.x < 0.5)m_position.x = 0.5;
			if (target_pos.z > 15.5)m_position.z = 14.5;
			if (target_pos.z < 0.5)m_position.z = 0.5;
					}
	}
	if (m_input->GetKeyHold('S'))
	{
		if (CanMoveHere(m_position - forward))
		{
			
			m_position -=forward*m_moveSpeed*timestep;
			didJustMove = true;
		}
		else {
			Vector3 target_pos = m_position - forward;
			if (target_pos.x > 15.5) m_position.x = 14.5;
			if (target_pos.x < 0.5)m_position.x = 0.5;
			if (target_pos.z > 15.5)m_position.z = 14.5;
			if (target_pos.z < 0.5)m_position.z = 0.5;
		}
		
	}
	if (m_input->GetKeyHold('A'))
	{
		if (CanMoveHere(m_position - right))
		{
			
			m_position -= right*m_moveSpeed*timestep;
			didJustMove = true;
		}
		else {
			Vector3 target_pos = m_position - right;
			if (target_pos.x > 15.5) m_position.x = 14.5;
			if (target_pos.x < 0.5)m_position.x = 0.5;
			if (target_pos.z > 15.5)m_position.z = 14.5;
			if (target_pos.z < 0.5)m_position.z = 0.5;
		}
	}
	if (m_input->GetKeyHold('D'))
	{
		if (CanMoveHere(m_position + right))
		{
			
			m_position += right*m_moveSpeed*timestep;
			didJustMove = true;
		}
		else {
			Vector3 target_pos = m_position + right;
			if (target_pos.x > 15.5) m_position.x = 14.5;
			if (target_pos.x < 0.5)m_position.x = 0.5;
			if (target_pos.z > 15.5)m_position.z = 14.5;
			if (target_pos.z < 0.5)m_position.z = 0.5;
		}
	}

	//if (didJustMove)
	//{
	//	// We want to react once per move (not every frame)
	//	FinishTurn();
	//}
}

void Player::FinishTurn()
{
	// Even though this is called in an Update function, it's essentially event-driven as it
	// is only called the frame we receive input from the keyboard.

	// React to tile we're standing on
	//ReactToTile();
	//CheckIfTrapped();

	// Decrease moves remaining
	

	// Show health visually as scale of player mesh
	//SetUniformScale(m_health / 100.0f);
}

bool Player::CanMoveHere(Vector3 target)
{
	// Asks the GameBoard for the type of the target tile
	// We can't step onto a wall or a disabled tile
	float x = target.x;
	float z = target.z;
	if (x < 0.5 || x>15.5 || z > 15.5 || z < 0.5) {
		return false;
	}
	return true;
}

void Player::CheckIfTrapped()
{
	// Using our target position, ask the GameBoard for the type of 
	// our surrounding tiles and check if we are surrounded by walls or grey tiles

	m_isTrapped = !CanMoveHere(m_position + Vector3(0, 0, 1)) &&  // Above
		!CanMoveHere(m_position + Vector3(0, 0, -1)) && // Below
		!CanMoveHere(m_position + Vector3(-1, 0, 0)) && // Left
		!CanMoveHere(m_position + Vector3(1, 0, 0));    // Right
}

void Player::ReactToTile()
{
	TileType targetTileType = m_currentBoard->GetTileTypeForPosition(m_position.x, m_position.z);

	switch (targetTileType)
	{
	case TileType::HEALTH:
		m_health += 5;
		if (m_health > 100.0f) { m_health = 100; }		break;
	case TileType::DAMAGE:
		m_health -= 10;
		break;
	case TileType::TELEPORT:
		TeleportToTileOfType(TileType::TELEPORT);
		break;
	case TileType::MONSTER_VAR1:
	case TileType::MONSTER_VAR2:
		// We'll react the same to both types of monster. TODO how could we differentiate them?
		m_monster->rest();
		DoMonsterBattle();
		break;
	default:
		break;
	}
}

void Player::TeleportToTileOfType(TileType type)
{
	Tile* destinationTile = m_currentBoard->GetRandomTileOfType(type);

	if (destinationTile)
	{
		// We need to set both the current position and the target
		// The only time the player remains still is when these two positions match
		
		m_position = destinationTile->GetPosition();

		// Tiles start up in the sky and fall down. Ensure player starts on the ground.
		
		m_position.y = 0.0f;
	}
}

int Player::Attack()
{
	// The player is much stronger than any monster on the board
	return MathsHelper::RandomRange(0, 20);
}

void Player::BeHit(int amount)
{
	// "abs" keeps a value positive
	m_health -= abs(amount);
}

void Player::DoMonsterBattle()
{
	// A battle takes place within a single frame.

	// Slightly hacky, but we only need a Monster when a battle is about to occur.
	// The Player creates a Monster then fights it. Asking the GameBoard for a Monster
	// would perhaps be a more proper way of doing this, however storing Monsters in Tiles
	// would be unnecessary work for this implementation.
	

	// We keep fighting until someone dies
	while (m_health > 0 && m_monster->IsAlive())
	{
		int playerAttackValue = Attack();
		int monsterAttackValue = m_monster->Attack();

		if (playerAttackValue > monsterAttackValue)
		{
			// Player wins the round - the monster will receive some damage
			m_monster->BeHit(playerAttackValue - monsterAttackValue);
		}
		else
		{
			// Monster wins round - the player will receive some damage
			BeHit(monsterAttackValue - playerAttackValue);
		}
	}

	if (!m_monster->IsAlive())
	{
		// If the player won the overall battle, increment our score
		m_score += m_monster->GetSkill();
		m_monstersDefeated++;
	}
}

