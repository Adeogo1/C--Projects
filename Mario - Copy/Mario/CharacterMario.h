#pragma once
#include "Character.h"
#include "TextureAnim.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Input.h"
#include "Collisions.h"
#include "Collider.h"






class CharacterMario : public Character
{
public:
	CharacterMario(Properties* props);
	virtual void Render();
	virtual void Update(float deltaTime);
	virtual void Clean();
	Collider* GetCollider() { return m_Collider; }
	//getters and setters
	void SetCanMove(bool canMove) {m_canMove = canMove;}
	~CharacterMario();

private:
	void AnimState();
	void SmallMario(float deltaTime) {}
	void BigMario(float deltaTime) {}
	void FireMario(float deltaTime) {}
	//int m_Row, m_Frame, m_FrameCount;
	//int m_AnimSpeed;//animation speed

	float m_MarioState;//1 - small mario, 2 - big mario, 3 - fire mario



	//UI
	


	//Jumping
	bool m_IsJumping;
	bool m_IsGrounded;
	bool m_isFalling;
	float m_JumpTime;
	float m_JumpForce;

	//crouching
	bool m_IsCrouching;

	//moving
	bool m_canMove;
	bool m_IsFacingRight;
	SDL_RendererFlip facingDir;
	bool m_IsGliding;
	float m_Speed;
	bool m_isRunning;
	float m_GlideTime;

	//attack time
	float m_shootTime;
	float shootcount;
	bool m_isShooting;

	Collider* m_Collider;//box arround the player//for map
	Vector2D m_lastSafePosition;// save point// if the player hit the wall you need to bring it back to the flast safe position he hadbefore the collision
	Animation* m_Animation;
	RigidBody* m_RigidBody;//player physics
	//LevelMap* m_current_level_map;



};
