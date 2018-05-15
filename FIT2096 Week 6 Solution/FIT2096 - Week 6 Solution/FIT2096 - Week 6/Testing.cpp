#include "testing.h"

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

void Monster::Update(float timestep)
{
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