/*	FIT2096 - Assignment 1 Sample Solution
*	Monster.h
*	Created by Mike Yeates - 2017 - Monash University
*	A simpe object which has a health, can attack, and can be hit.
*/

#ifndef MONSTER_H
#define MONSTER_H

class Monster
{
private:
	int m_health;
	int m_skill;
	bool m_isAlive;

public:
	Monster();
	~Monster();

	int Attack();
	void BeHit(int amount);

	void rest();
	bool IsAlive() { return m_isAlive; }
	int GetSkill() { return m_skill; }

};

#endif