#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "GameObject.h"
#include"Commons.h"
#include "Constants.h"
#include "Texture2D.h"
#include "Vector2D.h"
#include "Point.h"
#include "TextureAnim.h"
#include "Transform.h"
#include <iostream>
#include <vector>
#include "LevelMap.h"
using namespace std;


class Texture2D;






class Character : public GameObject
{
public:
	Character(Properties* props) : GameObject(props) {}

	virtual void Render();
	virtual void Update(float deltaTime);
	virtual void Clean(){}
	~Character();
	
	void SetPosition(Transform* new_position);
	Transform* GetPosition();
	//inline Rect2D GetCollisionBox() {
	//	return Rect2D(m_Position->X, m_Position->Y, m_texture->GetWidth(), m_texture->GetHeight());
	//}
	/*inline CircleCollider GetCollisionCircle() {
		return CircleCollider(15.0f, m_Transform->X, m_Transform->Y);
	}*/
	void SetAlive(bool isAlive) { m_alive = isAlive; }
	bool GetAlive() { return m_alive; }
	float GetCollisionRadius();
	//Texture2D* GetTexture() { return m_texture; }

private:
	//FACING m_facing_direction;
	//LevelMap* m_current_level_map;

protected:
	/*SDL_Renderer* m_renderer;
	Vector2D m_Velocity;
	Texture2D* m_texture;
	float sprintMultiplier;*/
	float m_collisionRadius;
	bool m_alive = true;

};


