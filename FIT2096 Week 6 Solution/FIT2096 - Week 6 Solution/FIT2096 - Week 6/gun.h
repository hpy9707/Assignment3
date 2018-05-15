#ifndef GUN_H
#define GUN_H
#include"BulletManager.h"
class Gun {
private:
	BulletManager* m_bulletManager;

	int m_clipsCapacity;
	int m_currentClips;

	int m_magazineCapacity;

	float m_reloadTime;
	float m_currentReloading;

	float m_fireFrequency;
	float m_fireTimer;

	bool m_startReloading;

public:
	Gun(BulletManager* bulletManager, int clipsCapacity, float reloadTime, float fireFrequency);
	~Gun();

	void Shoot(Vector3 position, Vector3 forward);
	void Reloading();
	void Update(float timestep);

	int GetMagazineCapacity() { return m_magazineCapacity; }
	int GetCurrentClip() { return m_currentClips; }
	void SetMagazineCapacity(int newCapacity);
};




#endif