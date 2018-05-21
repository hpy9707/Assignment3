#include "Healing.h"

Healing::Healing(Mesh * mesh, Shader * shader, Texture * texture, Vector3 position):GameObject(mesh,shader,texture,position)
{
	used = true;
	m_boundingBox = CBoundingBox(m_position + m_mesh->GetMin(), m_position + m_mesh->GetMax());
}

void Healing::OnPlayerCollisionEnter()
{
	used = false;
}

