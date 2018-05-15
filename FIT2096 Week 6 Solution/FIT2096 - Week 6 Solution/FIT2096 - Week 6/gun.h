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
	bool m_fire;

public:
	Gun(BulletManager* bulletManager, int clipsCapacity, float reloadTime, float fireFrequency);
	~Gun();

	void Shoot(Vector3 position, Vector3 forward);
	void Reloading();
	void Update(float timestep);

	bool getFire() { return m_fire; }
	bool getreload() { return m_startReloading; }
	int GetMagazineCapacity() { return m_magazineCapacity; }
	int GetCurrentClip() { return m_currentClips; }
	void SetMagazineCapacity(int newCapacity);
	void setReload(bool state) { m_startReloading = state; }
	void setFire(bool fire) { m_fire = fire; }
};




#endif