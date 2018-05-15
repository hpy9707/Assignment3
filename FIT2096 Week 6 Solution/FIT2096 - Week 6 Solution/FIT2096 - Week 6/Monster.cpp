#include "Monster.h"



void Monster::LookAt(Vector3 Target)
{
	
	Vector3 offset = Target - m_position;
	Vector3 ne = Vector3(0, 0, 1);
	float dis = Vector3::Distance(m_position, Target);
	float cosine = (offset.Dot(ne)) / dis;
	float angle = acos(cosine);
	if (Target.x < m_position.x) {
		m_rotY = -angle;
	}
	else {
		m_rotY = angle;
	}
}

void Monster::Moving(float timestep,Vector3 target_position)
{
	switch (m_type)
	{
	case 1:
		runway1(target_position, timestep);
		break;
	case 2:
		runway2(target_position, timestep);
		break;
	case 3:runway3(target_position, timestep); break;
	case 4:runway4(target_position, timestep); break;
	case 5:runway5(target_position, timestep); break;

	default:
		break;
	}
}




int Monster::Attack()
{
	// A monster's attack power is limited to its skill
	return MathsHelper::RandomRange(0, m_skill);
}

void Monster::BeHit(int amount)
{
	// "abs" keeps a value positive
	m_health -= abs(amount);

	if (m_health <= 0)
	{
		m_isAlive = false;
	}
}

void Monster::rest()
{
	m_skill = MathsHelper::RandomRange(8, 15);
	m_isAlive = true;
}

void Monster::runway1(Vector3 target, float timestep)
{
	
	
		Vector3 dis = m_position - target;
		dis.Normalize(); 
		float distance = Vector3::Distance(target, m_position);
		if(m_moving) {
			m_position -= dis*timestep*m_movespeed;
			}
		if (distance < 0.1f)
			m_moving = false;
		else m_moving = true;
	
}
void Monster::runway2(Vector3 target, float timestep)
{
}

void Monster::runway3(Vector3 target, float timestep)
{
}

void Monster::runway4(Vector3 target, float timestep)
{
}

void Monster::runway5(Vector3 target, float timestep)
{
}

Monster::Monster()
{
	m_health = 20;
	m_movespeed = 4.0f;
	m_moving = true;
}

Monster::Monster(Mesh * mesh, Shader * shader, Texture * texture, Vector3 position, int type):GameObject(mesh,shader,texture,position)
{
	m_type = type;
	m_health = 20;
	m_movespeed =1.0f;
	m_moving = true;
}

Monster::~Monster()
{
}

