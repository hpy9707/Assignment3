#include "Monster.h"

Monster::Monster()
{
	m_health = 20;
	m_movespeed = 4.0f;
	m_moving = true;
	original_position = m_position;
	facelocation = true;
	random_position = Vector3(MathsHelper::RandomRange(1.0f, 14.0f), 0, MathsHelper::RandomRange(1.0f, 14.0f));
}

Monster::Monster(Mesh * mesh, Shader * shader, Texture * texture, Vector3 position, int type) :GameObject(mesh, shader, texture, position)
{
	m_type = type;
	m_health = 20;
	m_movespeed = 1.0f;
	m_moving = true;
	original_position=m_position;
	facelocation = true;
	random_position = Vector3(MathsHelper::RandomRange(1.0f, 14.0f), 0, MathsHelper::RandomRange(1.0f, 14.0f));
}


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
	case 3:runway3( timestep); break;
	case 4:
		runway4( timestep); break;
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
	Vector3 dis = m_position - target;
	dis.Normalize();
	
	
		m_position += dis*timestep*m_movespeed;
	
		if (m_position.x > 14) m_position.x = 14;
		if (m_position.x < 0.75)m_position.x = 0.75;
		if (m_position.z > 14)m_position.z = 14;
		if (m_position.z < 0.75)m_position.z = 0.75;
}

void Monster::runway3( float timestep)
{
	Vector3 dis = m_position - random_position;
	dis.Normalize();
	float distance = Vector3::Distance(random_position, m_position);
	if (distance > 0.1f) {
		m_position -= dis*timestep*m_movespeed;
	}
	else
		random_position = Vector3(MathsHelper::RandomRange(1.0f, 14.0f), 0, MathsHelper::RandomRange(1.0f, 14.0f));
}

void Monster::runway4( float timestep)
{
	Vector3 dis = original_position - random_position;
	dis.Normalize();
	if (facelocation)
	{
		float distance = Vector3::Distance(m_position, random_position);
		if (distance > 0.1f) 
			m_position -= dis*timestep*m_movespeed;
		else
			facelocation = false;
	}
	else {
		float distance = Vector3::Distance(m_position, original_position);
		if (distance > 0.1f)
			m_position += dis*timestep*m_movespeed;
		else facelocation = true;
	}
	

}

void Monster::runway5(Vector3 target, float timestep)
{

	float distance = Vector3::Distance(m_position, target);
	if (distance < 1.5f)
	{
		m_position = random_position;
		random_position = Vector3(MathsHelper::RandomRange(1.0f, 15.0f), 0, MathsHelper::RandomRange(1.0f, 15.0f));
	}
}


Monster::~Monster()
{
}

