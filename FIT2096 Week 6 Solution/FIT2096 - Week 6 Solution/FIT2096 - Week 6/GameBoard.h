#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "Tile.h"
#include "MeshManager.h"
#include "TextureManager.h"

class GameBoard
{
private:
	MeshManager* m_meshManager;
	TextureManager* m_textureManager;
	Shader* m_tileShader;

	// How many tiles does this board manage
	const static int BOARD_WIDTH = 16;
	const static int BOARD_HEIGHT = 16;

	// Storing tiles in a 2D array to make neighbour checking easier
	Tile* m_tiles[BOARD_HEIGHT][BOARD_WIDTH];
	std::vector<Tile*> m_shortlist;
	void Generate();
	void AddWalls();

public:
	GameBoard();
	GameBoard(MeshManager* meshManager, TextureManager* textureManager, Shader* tileShader);
	~GameBoard();

	void Update(float timestep);
	void Render(Direct3D* renderer, Camera* camera);

	
	TileType GetTileTypeForPosition(int x, int z);
	Tile* GetRandomTileOfType(TileType type);
	std::vector<Tile*>* getalltile() { return &m_shortlist; }//??????
	//teleport???

};

#endif