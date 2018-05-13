#include "testing.h"

void Testing::LookAt(Vector3 Target)
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

void Testing::Update(float timestep)
{
}
