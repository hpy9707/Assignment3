#ifndef TILE_H
#define TILE_H

#include "GameObject.h"
#include "TextureManager.h"

// Define all the types of tiles we could be (naming these by function instead of appearance).
enum class TileType
{
	HEALTH,
	DAMAGE,
	TELEPORT,
	NORMAL,
	DISABLED,
	MONSTER_VAR1,
	MONSTER_VAR2,
	WALL,
	INVALID // Used if we query a tile which doesn't exist
};

class Tile : public GameObject
{
private:
	TileType m_type;
	TextureManager* m_textureManager;

	TileType SelectType();
	Texture* GetTextureForType(TileType type);
	CBoundingBox m_CBbox;
public:
	Tile();
	Tile(Mesh* mesh, Shader* shader, Vector3 pos, TextureManager* textureManager);
	Tile(Mesh* mesh, Shader* shader, Vector3 pos, TextureManager* textureManager, TileType type);
	~Tile();

	CBoundingBox getBound() { return m_CBbox; }
	void Update(float timestep);
	TileType GetType() { return m_type; }
	void SetType(TileType type);

};

#endif

