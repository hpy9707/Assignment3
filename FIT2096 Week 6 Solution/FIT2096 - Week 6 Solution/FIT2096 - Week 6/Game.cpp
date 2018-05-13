/*	FIT2096 - Example Code
*	Game.cpp
*	Created by Elliott Wilson & Mike Yeates - 2016 - Monash University
*/

#include "Game.h"
#include "TexturedShader.h"
#include"tile.h"
#include "StaticObject.h"
#include"MathsHelper.h"
#include "FlyingCamera.h"
#include "ThirdPersonCamera.h"

#include "DirectXTK/CommonStates.h"
#include <sstream>

Game::Game()
{
	m_renderer = NULL;
	m_currentCam = NULL;
	m_input = NULL;
	m_meshManager = NULL;
	m_textureManager = NULL;
	m_diffuseTexturedShader = NULL;
	m_unlitVertexColouredShader = NULL;
	m_spriteBatch = NULL;
	m_arialFont12 = NULL;
	m_arialFont18 = NULL;
	m_button = NULL;
	m_gameboard = NULL;
	m_player = NULL;
}

Game::~Game() {}

bool Game::Initialise(Direct3D* renderer, InputController* input)
{
	m_renderer = renderer;	
	m_input = input;
	m_meshManager = new MeshManager();
	m_textureManager = new TextureManager();

	if (!InitShaders())
		return false;

	if (!LoadMeshes())
		return false;

	if (!LoadTextures())
		return false;

	LoadFonts();
	InitUI();
	InitGameWorld();
	RefreshUI();

	m_currentCam = new FlyingCamera(m_input, m_player->GetPosition()+Vector3(0,0.5,0));
	//m_currentCam = new ThirdPersonCamera(m_player, Vector3(0, 10, -25), true, 2.0f);

	return true;
}

bool Game::InitShaders()
{
	m_unlitVertexColouredShader = new Shader();
	if (!m_unlitVertexColouredShader->Initialise(m_renderer->GetDevice(), L"Assets/Shaders/VertexShader.vs", L"Assets/Shaders/VertexColourPixelShader.ps"))
		return false;

	m_diffuseTexturedShader = new TexturedShader();
	if (!m_diffuseTexturedShader->Initialise(m_renderer->GetDevice(), L"Assets/Shaders/VertexShader.vs", L"Assets/Shaders/TexturedPixelShader.ps"))
		return false;

	return true;
}

bool Game::LoadMeshes()
{
	if (!m_meshManager->Load(m_renderer, "Assets/Meshes/floor_tile.obj"))
		return false;

	if (!m_meshManager->Load(m_renderer, "Assets/Meshes/wall_tile.obj"))
		return false;

	if (!m_meshManager->Load(m_renderer, "Assets/Meshes/player_capsule.obj"))
		return false;


	if (!m_meshManager->Load(m_renderer, "Assets/Meshes/enemy.obj"))
		return false;

	return true;
}

bool Game::LoadTextures()
{
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_blue.png"))
		return false;

	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_disabled.png"))
		return false;

	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_green.png"))
		return false;

	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_red2.png"))
		return false;

	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_red3.png"))
		return false;

	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_red1.png"))
		return false;

	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_white.png"))
		return false;
		

	if (!m_textureManager->Load(m_renderer, "Assets/Textures/button.png"))
		return false;
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/sprite_healthBar.png"))
		return false;

	return true;
}

void Game::LoadFonts()
{
	// There's a few different size fonts in there, you know
	m_arialFont12 = new SpriteFont(m_renderer->GetDevice(), L"Assets/Fonts/Arial-12pt.spritefont");
	m_arialFont18 = new SpriteFont(m_renderer->GetDevice(), L"Assets/Fonts/Arial-18pt.spritefont");
}

void Game::InitUI()
{
	m_spriteBatch = new SpriteBatch(m_renderer->GetDeviceContext());

	// Init Buttons
	m_button = new Button(128, 64, m_textureManager->GetTexture("Assets/Textures/button.png"), L"I'm a button", Vector2(80, 50), m_spriteBatch, m_arialFont12, m_input, [this]
	{
		OnButtonPress();
	});
	for (int i = 0; i < 10; i++) {
		m_currentItemSprite[i] = m_textureManager->GetTexture("Assets/Textures/sprite_healthBar.png");
	}
	
}

void Game::OnButtonPress()
{
	MessageBox(0, "Lambda's are awesome!", "It's magic", MB_OK);
}



void Game::RefreshUI()
{
	// Ensure text in UI matches latest scores etc (call this after data changes)
	// Concatenate data into our label string using a wide string stream
	if (m_player)
	{
		std::wstringstream ss;

		// Round to two decimal places for neater output
		ss << "Your score: " <<m_player->GetScore();

		m_distanceTravelledText = ss.str();
	}
	if(!m_player->getmonsterAlive())
	{
		std::wstringstream ss;

		// Round to two decimal places for neater output
		ss << "You kill the monster! " ;

		m_monsterkilled = ss.str();
	}
	
}

void Game::InitGameWorld()
{
	m_gameboard = new GameBoard(m_meshManager, m_textureManager, m_diffuseTexturedShader);
	m_player = new Player(m_meshManager->GetMesh("Assets/Meshes/player_capsule.obj"),
		m_diffuseTexturedShader,
		m_textureManager->GetTexture("Assets/Textures/tile_white.png"),
		m_input,
		m_gameboard);
	for (int x = 0; x < 16; x++) {
		for (int z = 0; z < 16; z++)
		{
			if (m_gameboard->GetTileTypeForPosition(x, z) == TileType::MONSTER_VAR1 || m_gameboard->GetTileTypeForPosition(x, z) == TileType::MONSTER_VAR2)
			{
				m_monsterMesh.push_back(new Testing(m_meshManager->GetMesh("Assets/Meshes/enemy.obj"),
					m_diffuseTexturedShader, 
					m_textureManager->GetTexture("Assets/Textures/tile_red3.png"),
					Vector3(x,0,z)));
			}
			if (m_gameboard->GetTileTypeForPosition(x, z) == TileType::HEALTH ){
				m_capsuleMesh.push_back(new StaticObject(m_meshManager->GetMesh("Assets/Meshes/player_capsule.obj"),
					m_diffuseTexturedShader,
					m_textureManager->GetTexture("Assets/Textures/tile_green.png"),
					Vector3(x, 0.25, z-0.25)));
			}
		}
		for (int i = 0; i <m_monsterMesh.size(); i++) {
			m_monsterMesh[i]->SetUniformScale(0.5f);
		}
		for (int i = 0; i <m_capsuleMesh.size(); i++) {
			m_capsuleMesh[i]->SetXRotation(ToRadians(90.0f));
			m_capsuleMesh[i]->SetUniformScale(0.5f);
		}
	}

}

void Game::Update(float timestep)
{
	m_input->BeginUpdate();
	for (unsigned int i = 0; i < m_monsterMesh.size(); i++)
	{
		
			m_monsterMesh[i]->Update(timestep);
			if (m_monsterMesh[i]->GetPosition() == m_player->GetPosition()) {
				Testing* temp;
				temp = m_monsterMesh[i];
				 m_monsterMesh[i] =m_monsterMesh[m_monsterMesh.size()-1];
				  m_monsterMesh[m_monsterMesh.size() - 1] = temp;
				 m_monsterMesh.pop_back();
				//delete m_gameObjects[i]; 
				//m_monsterMesh.erase(m_monsterMesh.begin() + i);
			}
			else {
				m_monsterMesh[i]->LookAt(m_player->GetPosition());
			}
		
	}

	/*for (int i = m_monsterMesh.size() - 1; i >= 0; i--) {
		if (m_monsterMesh[i] == NULL) { m_monsterMesh.erase(m_monsterMesh.begin() +i); }
	}*/
	for (unsigned int i = 0; i < m_capsuleMesh.size(); i++) {
		m_capsuleMesh[i]->Update(timestep);
		Vector3 actualpos;
		actualpos.x = m_capsuleMesh[i]->GetPosition().x;
		actualpos.y = 0;
		actualpos.z= m_capsuleMesh[i]->GetPosition().z+0.25;
		if (actualpos == m_player->GetPosition()) {
			GameObject* temp;
			temp = m_capsuleMesh[i];
			m_capsuleMesh[i] = m_capsuleMesh[m_capsuleMesh.size() - 1];
			 m_capsuleMesh[m_capsuleMesh.size() - 1] = temp;
			m_capsuleMesh.pop_back();
		}
	}
	m_gameboard->Update(timestep);
	m_player->Update(timestep);
	checkgameover();
	m_currentCam->SetPosition(m_player->GetPosition() + Vector3(0, 0.5, 0));
	//m_button->Update();
	RefreshUI();
	m_currentCam->Update(timestep);

	m_input->EndUpdate();
}

void Game::Render()
{
	m_renderer->BeginScene(0.2f, 0.2f, 0.2f, 1.0f);
	for (unsigned int i = 0; i < m_monsterMesh.size(); i++)
	{
		if (m_monsterMesh[i] != NULL) {
			m_monsterMesh[i]->Render(m_renderer, m_currentCam);
		}
	}
	for (unsigned int i = 0; i < m_capsuleMesh.size(); i++)
	{
		m_capsuleMesh[i]->Render(m_renderer, m_currentCam);
	}
	m_gameboard->Render(m_renderer, m_currentCam);
	m_player->Render(m_renderer, m_currentCam);
	DrawUI();

	m_renderer->EndScene();		
}

void Game::DrawUI()
{
	// Sprites don't use a shader 
	m_renderer->SetCurrentShader(NULL);

	CommonStates states(m_renderer->GetDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, states.NonPremultiplied());

	// Do UI drawing between the Begin and End calls

	// Tell our button to draw itself
	//m_button->Render();

	// Let's draw some text over our game
	m_arialFont18->DrawString(m_spriteBatch, m_distanceTravelledText.c_str(), Vector2(20,40), Color(1.0f, 1.0f, 1.0f), 0, Vector2(0,0));
	m_arialFont18->DrawString(m_spriteBatch, m_monsterkilled.c_str(), Vector2(20, 60), Color(1.0f, 1.0f, 1.0f), 0, Vector2(0, 0));
	// Here's how we draw a sprite over our game
	float currHp = m_player->GetHealth();
	float num_of_bar = ceil(currHp / 10);
	for (int i = 0; i < (int)num_of_bar; i++) {
		m_spriteBatch->Draw(m_currentItemSprite[i]->GetShaderResourceView(), Vector2(20+i*10, 20), Color(1.0f, 0.0f, 0.0f));
	}
	m_spriteBatch->End();
}
void Game::checkgameover()
{
	const char* msg = "";

	if (m_player->GetHealth() <= 0.0f)
	{
		msg = "You've run out of health.";
	}
	
	else if (m_player->GetIsTrapped())
	{
		msg = "You're trapped.";
	}

	if (msg != "")
	{
		std::stringstream ss;
		ss << msg << " You scored " << m_player->GetScore() << " and defeated " << m_player->GetNumberOfMonstersDefeated() << " monsters.";

		// Message Boxes are a blocking call which makes life a little easier here
		MessageBox(NULL, ss.str().c_str(), "Game Over", MB_OK);
		PostQuitMessage(0);

		// From now on, an in-game UI should be used instead of a message box
	}
}

void Game::Shutdown()
{
	for (unsigned int i = 0; i <m_monsterMesh.size(); i++)
	{
		delete m_monsterMesh[i];
	}

	m_monsterMesh.empty();
	for (unsigned int i = 0; i <m_capsuleMesh.size(); i++)
	{
		delete m_capsuleMesh[i];
	}

	m_capsuleMesh.empty();

	if (m_currentCam)
	{
		delete m_currentCam;
		m_currentCam = NULL;
	}

	if (m_unlitVertexColouredShader)
	{
		m_unlitVertexColouredShader->Release();
		delete m_unlitVertexColouredShader;
		m_unlitVertexColouredShader = NULL;
	}

	if(m_diffuseTexturedShader)
	{
		m_diffuseTexturedShader->Release();
		delete m_diffuseTexturedShader;
		m_diffuseTexturedShader = NULL;
	}

	if (m_meshManager)
	{
		m_meshManager->Release();
		delete m_meshManager;
		m_meshManager = NULL;
	}

	if (m_textureManager)
	{
		m_textureManager->Release();
		delete m_textureManager;
		m_textureManager = NULL;
	}

	if (m_spriteBatch)
	{
		delete m_spriteBatch;
		m_spriteBatch = NULL;
	}

	if (m_arialFont12)
	{
		delete m_arialFont12;
		m_arialFont12 = NULL;
	}

	if (m_arialFont18)
	{
		delete m_arialFont18;
		m_arialFont18 = NULL;
	}

	if (m_button)
	{
		delete m_button;
		m_button = NULL;
	}
	if (m_gameboard) {
		delete m_gameboard;
		m_gameboard = NULL;
	}
	if (m_player) {
		delete m_player;
		m_player = NULL;
	}
}