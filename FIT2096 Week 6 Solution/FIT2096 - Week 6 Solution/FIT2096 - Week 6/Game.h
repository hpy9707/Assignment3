/*	FIT2096 - Example Code
*	Game.h
*	Created by Elliott Wilson & Mike Yeates - 2016 - Monash University
*	This class is the heart of our game and is also where our game logic will reside
*	It contains the overall Update and Render method for the whole game
*	You should eventually split some game logic into other objects which Game will manage
*	Watch the size of this class - it can grow out of control very fast!
*/

#ifndef GAME_H
#define GAME_H

#include "Direct3D.h"
#include "Camera.h"
#include "InputController.h"
#include "MeshManager.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Button.h"
#include "gameboard.h"
#include "player.h"
#include"BulletManager.h"

#include "DirectXTK/SpriteBatch.h"
#include "DirectXTK/SpriteFont.h"
#include "Monster.h"
#include"Healing.h"
#include"CollisionManager.h"
#include <vector>

class Game
{
private:
	Camera* m_currentCam;		
	Direct3D* m_renderer;
	InputController* m_input;
	MeshManager* m_meshManager;
	TextureManager* m_textureManager;
	CollisionManager* m_collisionManager;
	// Sprites / Fonts
	SpriteBatch* m_spriteBatch;
	SpriteFont* m_arialFont12;
	SpriteFont* m_arialFont18;

	// Our game will have a button (eventually you might want to manage a collection of these)
	Button* m_button;

	// Shaders
	Shader* m_unlitVertexColouredShader;
	Shader* m_diffuseTexturedShader;
	
	//game objects
	GameBoard* m_gameboard;
	std::vector<Player*> m_player;
	std::vector<Monster*> m_monsterMesh;
	std::vector<Healing*>m_capsuleMesh;
	BulletManager* m_bulletmanager;
	

	// Wide strings use more than 8 bits per character so they can capture more symbols
	// Windows loves them and as such so does Direct3D and its text helpers
	std::wstring m_distanceTravelledText;
	std::wstring m_monsterkilled;
	std::wstring m_state;

	Texture* m_currentItemSprite[10];

	// Initialisation Helpers
	bool InitShaders();
	bool LoadMeshes();
	bool LoadTextures();
	void LoadFonts();
	void InitGameWorld();

	void InitUI();
	void DrawUI();
	void RefreshUI();
	void OnButtonPress();
	void checkgameover();

public:
	Game();	
	~Game();

	bool Initialise(Direct3D* renderer, InputController* input); //The initialise method will load all of the content for the game (meshes, textures, etc.)

	void Update(float timestep);	//The overall Update method for the game. All gameplay logic will be done somewhere within this method
	void Render();					//The overall Render method for the game. Here all of the meshes that need to be drawn will be drawn

	void Shutdown(); //Cleanup everything we initialised
};

#endif