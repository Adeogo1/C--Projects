#include "Character.h"






Character::~Character() {
	//m_renderer = nullptr;
}

void Character::Render() {

}




//float Character::GetCollisionRadius() {
//	//return m_collisionRadius;
//	return 1.5f;
//}

//Rect2D Character::GetCollisionBox() {
//	return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight());
//}



void Character::Update(float deltaTime) {

	//int centralX_position = (int)(m_Position->X + (m_texture->GetWidth() * 0.5)) / TILE_WIDTH;
	//int foot_position = (int)(m_Position->Y + m_texture->GetHeight()) / TILE_HEIGHT;
	//deal with jumping first




 }

float Character::GetCollisionRadius() {
	return m_collisionRadius;
}

void Character::SetPosition(Transform* new_position) {
	m_Transform = new_position;
}
Transform* Character::GetPosition() {
	return m_Transform;
}