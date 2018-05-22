#include "Gun.h"

Gun::Gun(BulletManager * bulletManager, int clipsCapacity, float reloadTime, float fireFrequency)
{
	m_bulletManager = bulletManager;
	m_clipsCapacity = clipsCapacity;
	m_currentClips = m_clipsCapacity;
	m_reloadTime = reloadTime;
	m_currentReloading = m_reloadTime;
	m_fireFrequency = fireFrequency;
	m_fireTimer = m_fireFrequency;
	m_magazineCapacity = clipsCapacity*5;
	m_startReloading = false;
	m_fire = true;
}

Gun::~Gun()
{
	
}

void Gun::Shoot(Vector3 position, Vector3 forward)
{
	bool candoShoot = true;
	if (m_currentClips == 0)
		candoShoot = false;
	if (m_fireTimer >= 0)
		candoShoot = false;

	if (candoShoot) {
		m_bulletManager->CreateBullets(position, forward);
		m_fireTimer = m_fireFrequency;
		m_currentClips--;
	}
}

void Gun::Reloading()
{
	if (m_currentClips < m_clipsCapacity && m_magazineCapacity > 0) {
		int bulletNumber = m_clipsCapacity - m_currentClips;
		if (m_magazineCapacity <= bulletNumber) {
			m_currentClips += m_magazineCapacity;
			m_magazineCapacity = 0;
		}
		else {
			m_currentClips = m_clipsCapacity;
			m_magazineCapacity -= bulletNumber;
			
		}
		m_startReloading = false;
	}
}

void Gun::Update(float timestep)
{

	if (m_magazineCapacity == 0)
		m_startReloading = false;
	else if (m_currentClips == 0 && m_magazineCapacity != 0)
	{
		m_startReloading = true;
		m_fire = false;
	}



	if (m_startReloading) {
		if (m_currentReloading <= 0) {
			Reloading();
			m_currentReloading = m_reloadTime;
			m_startReloading = false;
			m_fire = true;
		}
		else {
			m_currentReloading -= timestep;
		}
	}


	m_fireTimer -= timestep;


}

void Gun::SetMagazineCapacity(int newCapacity)
{
	m_magazineCapacity = newCapacity;
}
