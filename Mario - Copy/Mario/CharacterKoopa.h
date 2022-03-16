#pragma once
#include "Character.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Animation.h"
#include "Engine.h"



class CharacterKoopa : public Character
{
public:
	CharacterKoopa(Properties* props);
	~CharacterKoopa();

	void TakeDamage();
	void Jump();
	void FlipRightWayUp();

	void Render() override;
	void Update(float deltaTime) override;
	virtual void Clean();
	Collider* GetCollider() { return m_collider; }
	Collider* GetDeadCollider() { return m_deadCollider; }
	
	bool GetInjured() { return m_injured; }


private:
	float m_movement_speed;
	Vector2D m_position;

	float m_single_sprite_w;
	float m_single_sprite_h;
	bool m_injured;
	float m_injured_time;
	LevelMap* m_current_level_map;

	bool m_IsFacingRight;
	SDL_RendererFlip facingDir;


	Collider* m_collider;
	Collider* m_deadCollider;
	RigidBody* m_rigidBody;
	bool m_IsGrounded;
	bool m_hasHitWall;
	Animation* m_SpriteSheetAnimation;
	Vector2D m_LastSafePosition;

};



