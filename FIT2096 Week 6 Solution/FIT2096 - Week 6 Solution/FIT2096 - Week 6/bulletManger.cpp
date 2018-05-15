#include "BulletManager.h"

BulletManager::BulletManager(MeshManager * meshmanager, TextureManager * texturemanager, Shader * shader)
{
	m_meshManager = meshmanager;
	m_textureManager = texturemanager;
	m_shader = shader;
	/*m_reloadTime = reloadtime;
	m_clipsCapacity = capacity;
	m_fireFrequency = firefrequency;*/
}

BulletManager::~BulletManager()
{
	for (unsigned int i = 0; i < m_allBullets.size(); i++)
	{
		delete m_allBullets[i];
	}

	m_allBullets.clear();
}

void BulletManager::CreateBullets(Vector3 position, Vector3 forward)
{
	float m_damage = SetBulletDamage();
	m_allBullets.push_back(new Bullet(m_meshManager->GetMesh("Assets/Meshes/bullet.obj"), m_shader, m_textureManager->GetTexture("Assets/Textures/bullet.png"), m_damage, position, forward));
}

void BulletManager::CheckAndDelete()
{
	for (int i = m_allBullets.size() - 1; i > 0; i--) {
		if (!m_allBullets[i]->getBulletalive()) {
			delete m_allBullets[i];
			m_allBullets.erase(m_allBullets.begin() + i);
		}
	}
}

void BulletManager::Update(float timestep)
{
	CheckAndDelete();
	for (unsigned int i = 0; i < m_allBullets.size(); i++)
	{
		m_allBullets[i]->Update(timestep);
	}
}

void BulletManager::Render(Direct3D * renderer, Camera * cam)
{
	for (unsigned int i = 0; i < m_allBullets.size(); i++)
	{
		m_allBullets[i]->Render(renderer, cam);
	}
}

float BulletManager::SetBulletDamage()
{
	return MathsHelper::RandomRange(5.0f, 10.0f);
}
