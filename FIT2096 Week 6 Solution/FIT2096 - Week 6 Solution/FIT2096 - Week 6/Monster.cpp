#include "Monster.h"

Monster::Monster()
{
	m_health = 20;
	m_movespeed = 4.0f;
	m_moving = true;
	original_position = m_position;
	facelocation = true;
	random_position = Vector3(MathsHelper::RandomRange(1.0f, 14.0f), 0, MathsHelper::RandomRange(1.0f, 14.0f));
	m_boundingBox = CBoundingBox(m_position + m_mesh->GetMin(), m_position + m_mesh->GetMax()+Vector3(0,-0.9,0));
	m_bulletmanager = NULL;
}

Monster::Monster(Mesh * mesh, Shader * shader, Texture * texture, Vector3 position, int type,BulletManager* bulletmanager) :GameObject(mesh, shader, texture, position)
{
	m_type = type;
	m_moving = true;
	original_position=m_position;
	facelocation = true;
	m_isAlive = true;
	m_bulletmanager = bulletmanager;
	initialproperty(type);//it will create different enemy property depending on enemy's type 
						  //Different type will affect health  movespeed and gun.
	random_position = Vector3(MathsHelper::RandomRange(1.0f, 14.0f), 0, MathsHelper::RandomRange(1.0f, 14.0f));
}

void Monster::initialproperty(int type)
{
	switch (type)
	{case 1:
		m_gun = new Gun(m_bulletmanager, 30, 10.0f, 2.0f);
		m_health = 10;
		m_movespeed = 2.0f;
		break;
	case 2:
		m_gun = new Gun(m_bulletmanager, 15, 10.0f, 1.0f);
		m_health = 20;
		m_movespeed = 1.5f;
		break;
	case 3:
		m_gun = new Gun(m_bulletmanager, 20, 2.0f, 0.5f);
		m_health = 30;
		m_movespeed = 1.0f;
		break;
	case 4:
		m_gun = new Gun(m_bulletmanager, 20, 10.0f, 1.0f);
		m_health = 40;
		m_movespeed = 1.5f;
		break;
	case 5:
		m_gun = new Gun(m_bulletmanager, 5, 10.0f, 5.0f);
		m_health = 50;
		m_movespeed = 0.0f;
		break;

	}
}

void Monster::Update(float timestep)
{
	LookAt();
	Moving(timestep);
	m_boundingBox.SetMin(m_position + m_mesh->GetMin());
	m_boundingBox.SetMax(m_position + m_mesh->GetMax() + Vector3(0, -0.9, 0));
	m_gun->Update(timestep);
	Vector3 target = Vector3::TransformNormal(Vector3(0, 0, 1), m_rotation);
	Vector3 bulletPosition = m_position + Vector3(0.09f, 0.6f, 0) + target;
	m_gun->Shoot(bulletPosition, target_pos - m_position);
}

void Monster::Render(Direct3D * renderer, Camera * cam)
{
	if (m_mesh) {
		//here is the function that each enemy will face to player
		m_rotation = MathsHelper::FacetoPlayer(m_position, target_pos, Vector3::Up);
		m_world = Matrix::CreateScale(m_scaleX, m_scaleY, m_scaleZ) * m_rotation * Matrix::CreateTranslation(m_position);
		m_mesh->Render(renderer, m_shader, m_world, cam, m_texture);
	}
}

void Monster::OnBulletCollisionEnter()
{
	m_health -= 7;
	if (m_health < 0) {
		m_isAlive = false;
	}
}

void Monster::OnBulletCollisionHeadEnter()//head sot die immediately
{
	m_health = 0;
	m_isAlive = false;
}


void Monster::LookAt()
{
	
	Vector3 offset = target_pos - m_position;
	Vector3 ne = Vector3(0, 0, 1);
	float dis = Vector3::Distance(m_position, target_pos);
	float cosine = (offset.Dot(ne)) / dis;
	float angle = acos(cosine);
	if (target_pos.x < m_position.x) {
		m_rotY = -angle;
	}
	else {
		m_rotY = angle;
	}
}

void Monster::Moving(float timestep)
{
	switch (m_type)
	{
	case 1:
		runway1( timestep);//chase player
		break;
	case 2:
		runway2(timestep);//far away from player
		break;
	case 3:runway3( timestep); break;//move to random position
	case 4:
		runway4( timestep); break;//always move to front of player
	case 5:runway5( timestep); break;// don't change position until player is near this enemy

	default:
		break;
	}
}

void Monster::runway1( float timestep)
{
		Vector3 dis = m_position - target_pos;
		dis.Normalize(); 
		float distance = Vector3::Distance(target_pos, m_position);
		if(m_moving) {
			m_position -= dis*timestep*m_movespeed;
			}
		if (distance < 0.5f)
			m_moving = false;
		else m_moving = true;
	
}
void Monster::runway2( float timestep)
{
	Vector3 dis = m_position - target_pos;
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
	Vector3 dis = m_position-m_faceingpos - target_pos;
	dis.Normalize();
	m_position -= dis*timestep*m_movespeed;
}

void Monster::runway5( float timestep)
{

	float distance = Vector3::Distance(m_position, target_pos);
	if (distance < 1.5f)
	{
		m_position = random_position;
		random_position = Vector3(MathsHelper::RandomRange(1.0f, 15.0f), 0, MathsHelper::RandomRange(1.0f, 15.0f));
	}
}
Monster::~Monster()
{
	if (m_gun) {
		delete m_gun;
		m_gun = NULL;
	}
	
	
}

