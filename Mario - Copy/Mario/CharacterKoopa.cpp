#include "CharacterKoopa.h"








CharacterKoopa::CharacterKoopa(Properties* props) : Character(props)
{
	facingDir = SDL_FLIP_NONE;
	m_IsFacingRight = false;
	m_hasHitWall = false;
	m_rigidBody = new RigidBody();
	m_rigidBody->SetGravity(3.5);
	m_collider = new Collider();
	m_collider->SetBuffer(0,0,0,0);
	m_injured = false;
	m_deadCollider = new Collider();
	m_deadCollider->SetBuffer(0,0,0,0);
	//m_current_level_map = map;
	//m_single_sprite_w = m_texture->GetWidth() / 2;
	//m_single_sprite_h = m_texture->GetHeight();
	m_SpriteSheetAnimation = new Animation();
	m_SpriteSheetAnimation->SetProps(m_TextureID, 0, 4, 100, facingDir);
	m_collisionRadius = 30.0f;
}

void CharacterKoopa::Render() {
	m_SpriteSheetAnimation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
	Vector2D cam = Camera::GetInstance()->GetPosition();

	SDL_Rect box = { (int)(m_collider->Get().x - cam.X),(int)(m_collider->Get().y - cam.Y), m_collider->Get().w,m_collider->Get().h };
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);

	Vector2D cam2 = Camera::GetInstance()->GetPosition();
	SDL_Rect box2 = { (int)(m_deadCollider->Get().x - cam2.X),(int)(m_deadCollider->Get().y - cam2.Y), m_deadCollider->Get().w,m_deadCollider->Get().h };
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box2);
}


void CharacterKoopa::Update(float deltaTime) {
	
	Character::Update(deltaTime);
	int centralX_position = (int)(m_Transform->X + m_single_sprite_w) / TILE_WIDTH;
	int foot_position = (int)(m_Transform->Y + m_single_sprite_h) / TILE_HEIGHT;

	facingDir = m_IsFacingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;


	if (!m_injured)
	{
		
		//enemy is not injured so move 
		if (m_Transform->X >= SCREEN_WIDTH )
		{
			m_IsFacingRight = false;
		}
		if (m_Transform->X + m_single_sprite_w <= 0)
		{
			m_IsFacingRight = false;
		}
	}
	else
	{
		//should not be moving when injured
		//set speed variable to false

		//count down the injured time
		m_injured_time -= deltaTime;

		if (m_injured_time <= 0.0)
			FlipRightWayUp();
	}

	if (m_hasHitWall)
	{
		m_rigidBody->ApplyForceX(-3 * FORWARDS);
		m_IsFacingRight = true;
	}
	else if (!m_hasHitWall)
	{
		m_rigidBody->ApplyForceX(3 );
		m_IsFacingRight = false;
	}


	//movement on x-axis
	m_rigidBody->Update(deltaTime);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->X += m_rigidBody->Position().X;
	m_collider->Set(m_Transform->X, m_Transform->Y, 30, 30);
	m_deadCollider->Set(m_Transform->X, m_Transform->Y, 30, 30);

	if (Collisions::Instance()->MapCollision(m_collider->Get()))
	{
		m_hasHitWall = !m_hasHitWall;
		m_Transform->X = m_LastSafePosition.X;

	}
	else
	{

	}


	//movement on y-axis
	m_rigidBody->Update(deltaTime);
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->Y += m_rigidBody->Position().Y;
	m_collider->Set(m_Transform->X, m_Transform->Y, 30, 30);
	m_deadCollider->Set(m_Transform->X, m_Transform->Y, 30, 30);

	if (Collisions::Instance()->MapCollision(m_collider->Get()))
	{

		m_IsGrounded = true;
		m_Transform->Y = m_LastSafePosition.Y;
	}
	else
	{
		m_IsGrounded = false;
	}
	m_SpriteSheetAnimation->SetProps(m_TextureID, 0, 4, 100, facingDir);
	m_SpriteSheetAnimation->Update(deltaTime);
	
}


void CharacterKoopa::TakeDamage() {
	m_injured = true;
	m_injured_time = INJURED_TIME;
	Jump();
}

void CharacterKoopa::Jump() {
	//if (!m_isJumping)
	//{
	//	m_jumpForce = JUMP_FORCE;
	//	m_isJumping = true;
	//	m_canJump = false;
	//}
}




void CharacterKoopa::FlipRightWayUp() {
	if (m_IsFacingRight == true)
	{
		m_IsFacingRight = false;
	}
	else
	{
		m_IsFacingRight = true;
	}

	m_injured = false;
	Jump();
}

void CharacterKoopa::Clean() {
	TextureAnim::GetInstance()->Clean();
}


CharacterKoopa::~CharacterKoopa()
{
	delete m_current_level_map;
	m_current_level_map = nullptr;
	delete m_collider;
	m_collider = nullptr;
	delete m_rigidBody;
	m_rigidBody = nullptr;
	delete m_SpriteSheetAnimation;
	m_SpriteSheetAnimation = nullptr;
}