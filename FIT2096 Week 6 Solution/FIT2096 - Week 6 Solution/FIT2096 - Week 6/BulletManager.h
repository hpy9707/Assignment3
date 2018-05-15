#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H
#include <vector>
#include "MeshManager.h"
#include "TextureManager.h"
#include "Bullet.h"
#include "MathsHelper.h"


class BulletManager {
private:
	MeshManager* m_meshManager;
	TextureManager* m_textureManager;
	Shader* m_shader;
	//int m_clipsCapacity;
	//float m_reloadTime;
	//float m_fireFrequency;


	std::vector<Bullet*> m_allBullets;



public:
	BulletManager(MeshManager* meshmanager, TextureManager* texturemanager, Shader* shader);
	~BulletManager();

	void CreateBullets(Vector3 position, Vector3 forward);
	void CheckAndDelete();
	void Update(float timestep);
	void Render(Direct3D* renderer, Camera* cam);
	float SetBulletDamage();





};
#endif // BULLETMANAGER_H

