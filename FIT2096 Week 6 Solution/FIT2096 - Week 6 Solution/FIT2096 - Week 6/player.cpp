#include "Player.h"

#include "MathsHelper.h"

Player::Player()
{
	m_input = NULL;
	m_moveSpeed = 2.5f;
	m_currentBoard = NULL;
	m_rotationSpeed = 0.75f;
	m_health = 100.0f;
	m_score = 0;
	m_monstersDefeated = 0;
	m_gun = NULL;
	m_boundingBox = CBoundingBox(m_position + m_mesh->GetMin(), m_position + m_mesh->GetMax());
}

Player::Player(Mesh* mesh, Shader* shader, Texture* texture, InputController* input, GameBoard* board ,BulletManager* bulletmanager) : GameObject(mesh, shader, texture, Vector3::Zero)
{
	m_input = input;
	m_moveSpeed = 2.5f;
	m_currentBoard = board;
	m_heading = 0.0f;
	m_pitch = 0.0f;
	m_rotationSpeed = 0.50f;
	m_health = 100.0f;
	m_score = 0;
	m_monstersDefeated = 0;
	TeleportToTileOfType(TileType::NORMAL);
	
	m_gun = new Gun(bulletmanager, 30, 2.0f, 0.2f);
}

Player::~Player() {
	if (m_gun) {
		delete m_gun;
		m_gun = NULL;
	}
}

void Player::Update(float timestep)
{
	m_boundingBox.SetMin(m_position + m_mesh->GetMin());
	m_boundingBox.SetMax(m_position + m_mesh->GetMax());
	
	m_gun->Update(timestep);
	// Constantly step towards target position
	// Could add a distance check here, however seeing we only have one player we'll be fine
	m_heading += m_input->GetMouseDeltaX() * m_rotationSpeed * timestep;
	m_pitch += m_input->GetMouseDeltaY() * m_rotationSpeed * timestep;
	Matrix heading = Matrix::CreateRotationY(m_heading);
	Matrix pitch = Matrix::CreateRotationX(m_pitch);

	Matrix lookAtRotation = pitch * heading;
	// Transform a world right vector from world space into local space
	Vector3 localRight = Vector3::TransformNormal(Vector3(1, 0, 0), heading);

	// Essentially our local forward vector but always parallel with the ground
	// Remember a cross product gives us a vector perpendicular to the two input vectors
	Vector3 localForwardXZ = localRight.Cross(Vector3(0, 1, 0));



	Vector3 right = Vector3::TransformNormal(Vector3(1, 0, 0), heading);

	// Essentially our local forward vector but always parallel with the ground
	// Remember a cross product gives us a vector perpendicular to the two input vectors
	Vector3 forward = localRight.Cross(Vector3(0, 1, 0));

	Vector3 target = Vector3::TransformNormal(Vector3(0, 0, 1), lookAtRotation);
	// We need to identify the frame input was received so we can perform common logic
	// outside of the GetKeyDown IF statements below.


	if (m_input->GetKeyHold('W'))
	{
		if (CanMoveHere(m_position + forward))
		{
			// Deactivate tile before we update the target position. This prevents the trail
			// of disabled tiles from getting ahead of the player. It always disables the tile
			// we are leaving as opposed to disabling the one we are moving onto.
			m_position += forward*m_moveSpeed*timestep;

		}
		else {
			resetpos(m_position + forward);
		}
	}
	if (m_input->GetKeyHold('S'))
	{
		if (CanMoveHere(m_position - forward))
		{

			m_position -= forward*m_moveSpeed*timestep;

		}
		else {
			resetpos(m_position - forward);
		}

	}
	if (m_input->GetKeyHold('A'))
	{
		if (CanMoveHere(m_position - right))
		{

			m_position -= right*m_moveSpeed*timestep;

		}
		else {
			resetpos(m_position - right);
		}
	}
	if (m_input->GetKeyHold('D'))
	{
		if (CanMoveHere(m_position + right))
		{

			m_position += right*m_moveSpeed*timestep;

		}
		else {
			resetpos(m_position + right);
		}
	}
	if (m_input->GetKeyDown('R')) {
		if (m_gun->GetMagazineCapacity() > 0) {
			m_gun->setReload(true);
			m_gun->setFire(false);
		}
	}
	if (m_input->GetMouseDown(LEFT_MOUSE)) {
		if (m_gun->getFire()) {
			Vector3 bulletPosition = m_position + Vector3(0, 0.5f, 0) + target;
			m_gun->Shoot(bulletPosition, target);
		}
	}

	//if (didJustMove)
	//{
	//	// We want to react once per move (not every frame)
	//	FinishTurn();
	//}
}

void Player::OnHealingCollisionEnter()
{
	m_health += 15;
	if (m_health > 100)
		m_health = 100;
}


bool Player::CanMoveHere(Vector3 target)
{
	// Asks the GameBoard for the type of the target tile
	// We can't step onto a wall or a disabled tile
	float x = target.x;
	float z = target.z;
	if (x < 0.75 || x>=14 || z >=14 || z < 0.75) {
		return false;
	}
	return true;
}

void Player::resetpos(Vector3 target_pos)
{
	if (target_pos.x > 14) m_position.x = 14;
	if (target_pos.x < 0.75)m_position.x = 0.75;
	if (target_pos.z > 14)m_position.z = 14;
	if (target_pos.z < 0.75)m_position.z = 0.75;
}



void Player::TeleportToTileOfType(TileType type)
{
	Tile* destinationTile = m_currentBoard->GetRandomTileOfType(type);

	if (destinationTile)
	{
		// We need to set both the current position and the target
		// The only time the player remains still is when these two positions match
		
		
		m_position = destinationTile->GetPosition();

	
	}
}


void Player::BeHit(int amount)
{
	// "abs" keeps a value positive
	m_health -= abs(amount);
}
int Player::GetPlayerClip()
{
	int clipNumber = m_gun->GetCurrentClip();
	return clipNumber;
}

int Player::GetPlayerMagazine()
{
	int magazineNumber = m_gun->GetMagazineCapacity();
	return magazineNumber;
}


