#include "Bullet.h"
#include "MathsHelper.h"

Bullet::Bullet(Mesh * mesh, Shader * shader, Texture * texture, float damage, Vector3 position, Vector3 forward) :GameObject(mesh, shader, texture, position)
{
	m_alive = true;
	m_speed = 5.0f;
	m_lifetime = 10.0f;
	m_damage = damage;
	m_forward = forward;
	m_forward.Normalize();

	m_boundingBox = CBoundingBox(m_position + m_mesh->GetMin(), m_position + m_mesh->GetMax());

}

void Bullet::Update(float timestep)
{
	if (m_alive) {
		m_position += m_forward*m_speed*timestep;
		m_boundingBox.SetMin(m_position + m_mesh->GetMin());
		m_boundingBox.SetMax(m_position + m_mesh->GetMax());
		m_lifetime -= timestep;
	}
	if (m_lifetime <= 0)
		m_alive = false;
}

void Bullet::Render(Direct3D * renderer, Camera * cam)
{
	if (m_mesh)
	{
		Matrix rotation = MathsHelper::FacetoPlayer(m_position, m_position + m_forward, Vector3::Up);
		m_world = Matrix::CreateScale(m_scaleX, m_scaleY, m_scaleZ) * rotation * Matrix::CreateTranslation(m_position);
		m_mesh->Render(renderer, m_shader, m_world, cam, m_texture);
	}
}

void Bullet::OnEnemyCollisionEnter()
{
	m_alive = false;
}

void Bullet::OnPlayerCollisionEnter()
{
	m_alive = false;
}
