#ifndef MONSTER_H
#define MONSTER_H
#include "GameObject.h"
#include "MathsHelper.h"
#include "math.h"

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
	void runway1(Vector3 target ,float timestep);
	void runway2(Vector3 target, float timestep);
	void runway3(float timestep);
	void runway4(float timestep);
	void runway5(Vector3 target, float timestep);
	void initialproperty(int type);
	
public:

	Monster();
	Monster(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position,int type) ;
	~Monster();
	void LookAt(Vector3 Target);
	void Moving(float timestep,Vector3 target_position );
	void Update(float timestep) {};
	void OnBulletCollisionEnter();
	void OnBulletCollisionHeadEnter();
	int Attack();
	void BeHit(int amount);

	void rest();
	bool IsAlive() { return m_isAlive; }
	int GetSkill() { return m_skill; }
	int Gettype() { return m_type; }
	CBoundingBox GetBounds() { return m_boundingBox; }
	
	

	
};
#endif
