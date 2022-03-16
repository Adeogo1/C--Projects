#pragma once
#include "GameObject.h"
#include "TextureAnim.h"
#include "Commons.h"
#include "Collider.h"
#include "Collisions.h"



class Coins : public Character
{
public:
	Coins(Properties* props);
	virtual void Render();
	virtual void Update(float deltaTime);
	virtual void Clean(string s);
	Collider* GetCollider() { return m_Collider; }
	~Coins();

private:
	Collider* m_Collider;//box arround the player//for map
	Vector2D m_lastSafePosition;// save point// if the player hit the wall you need to bring it back to the flast safe position he hadbefore the collision
	Animation* m_Animation;
};


