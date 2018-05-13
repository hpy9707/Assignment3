#include "Tile.h"
#include "MathsHelper.h"

Tile::Tile()
{
	m_type = TileType::NORMAL;
	m_textureManager = NULL;
	
}

Tile::Tile(Mesh* mesh, Shader* shader, Vector3 pos, TextureManager* textureManager)
	: GameObject(mesh, shader, NULL, pos)
{
	m_textureManager = textureManager;
	m_position = pos;


	// Also sets our texture
	SetType(SelectType());

	
}

Tile::Tile(Mesh* mesh, Shader* shader, Vector3 pos, TextureManager* textureManager, TileType type)
	: GameObject(mesh, shader, NULL, pos)
{
	m_type = type;
	m_textureManager = textureManager;
	m_position= pos;
	

	SetType(type);

	
}

Tile::~Tile() {}

void Tile::Update(float timestep)
{
	
}

TileType Tile::SelectType()
{
	// A Tile is responsible for selecting its own type (colour) using basic random numbers
	// Higher probability for normal white tiles than the rest

	int roll = MathsHelper::RandomRange(1, 100);

	if (roll < 67)
		return TileType::NORMAL;
	else if (roll < 71)
		return TileType::MONSTER_VAR1;
	else if (roll < 74)
		return TileType::MONSTER_VAR2;
	else if (roll < 78)
		return TileType::DAMAGE;
	else if (roll < 80)
		return TileType::HEALTH;
	else if (roll < 85)
		return TileType::TELEPORT;
	else
		return TileType::DISABLED;
}

Texture* Tile::GetTextureForType(TileType type)
{
	// Asks the texture manager for the texture matching our type (i.e. red texture for "damage" type)

	switch (type)
	{
	case TileType::HEALTH:
		return m_textureManager->GetTexture("Assets/Textures/tile_green.png");
	case TileType::DAMAGE:
		return m_textureManager->GetTexture("Assets/Textures/tile_red1.png");
	case TileType::TELEPORT:
		return m_textureManager->GetTexture("Assets/Textures/tile_blue.png");
	case TileType::DISABLED:
		return m_textureManager->GetTexture("Assets/Textures/tile_disabled.png");
	case TileType::MONSTER_VAR1:
		return m_textureManager->GetTexture("Assets/Textures/tile_red2.png");
	case TileType::MONSTER_VAR2:
		return m_textureManager->GetTexture("Assets/Textures/tile_red3.png");
	case TileType::NORMAL:
		return m_textureManager->GetTexture("Assets/Textures/tile_white.png");
	case TileType::WALL:
		return m_textureManager->GetTexture("Assets/Textures/tile_disabled.png");
	default:
		return m_textureManager->GetTexture("Assets/Textures/tile_white.png");
	}
}

void Tile::SetType(TileType type)
{
	m_type = type;
	m_texture = GetTextureForType(m_type);
}

