#include "Monster.h"
#include "MathsHelper.h"

Monster::Monster()
{
	m_health = 100;
	m_skill = MathsHelper::RandomRange(8, 15);
	m_isAlive = true;
}

Monster::~Monster() {}

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
