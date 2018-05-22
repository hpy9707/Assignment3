#ifndef MONSTER_H
#define MONSTER_H
#include "GameObject.h"
#include "MathsHelper.h"
#include "math.h"
#include"BulletManager.h"
#include"Gun.h"
#include"player.h"
class Monster : public GameObject
{
private:
	int m_health;
	int m_skill;
	bool m_isAlive;
	float m_movespeed;
	int m_type;
	bool m_moving;
	Vector3 random_position;
	Vector3 original_position;
	bool facelocation;
	CBoundingBox m_boundingBox;
	BulletManager* m_bulletmanager;
	Matrix m_rotation;
	Gun* m_gun;
	Vector3 target_pos;
	void runway1(float timestep);
	void runway2(float timestep);
	void runway3(float timestep);
	void runway4(float timestep);
	void runway5( float timestep);
	void initialproperty(int type);
	
public:

	Monster();
	Monster(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position, int type, BulletManager* bulletmanager);
	~Monster();
	
	void LookAt();
	void Moving(float timestep);
	void Update(float timestep) ;
	
	void Render(Direct3D * renderer, Camera * cam);
	void OnBulletCollisionEnter();
	void OnBulletCollisionHeadEnter();
	bool IsAlive() { return m_isAlive; }
	void SetTarget(Vector3 target) { target_pos = target; }
	int GetSkill() { return m_skill; }
	int Gettype() { return m_type; }
	CBoundingBox GetBounds() { return m_boundingBox; }
	
	

	
};
#endif
