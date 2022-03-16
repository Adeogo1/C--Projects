#include "CharacterMario.h"




CharacterMario::CharacterMario(Properties* props) : Character(props) {
	//m_current_level_map = map;
	facingDir = SDL_FLIP_NONE;
	m_GlideTime = GLIDE_TIME;
	m_Speed = BIG_MARIO_SPEED;
	m_IsGliding = false;
	m_IsCrouching = false;
	m_IsFacingRight = true;
	m_isRunning = false;
	m_alive = true;
	m_canMove = true;

	m_JumpTime = JUMP_TIME;
	m_JumpForce = JUMP_FORCE+10;

	m_Collider = new Collider();
	//m_Collider->Set(m_Transform->X, m_Transform->Y, 30, 64);
	m_Collider->SetBuffer(0, 0, 0, 0);

	m_RigidBody = new RigidBody();
	//m_RigidBody->SetGravity(8);

	m_Animation = new Animation();
	m_Animation->SetProps(m_TextureID, 0, 1, 100, facingDir);//3 for running anim
	m_collisionRadius = 15;

}

void CharacterMario::Render() {
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
	Vector2D cam = Camera::GetInstance()->GetPosition();

	SDL_Rect box = { (int)(m_Collider->Get().x - cam.X),(int)(m_Collider->Get().y - cam.Y), m_Collider->Get().w,m_Collider->Get().h };
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

void CharacterMario::Update(float deltaTime) {
	//	int centralX_position = (int)(m_Position->X + (m_texture->GetWidth() * 0.5)) / TILE_WIDTH;
		//int foot_position = (int)(m_Position->Y + m_texture->GetHeight()) / TILE_HEIGHT;

	m_IsCrouching = false;
	m_isRunning = false;

	m_RigidBody->UnSetForce();
	if (m_canMove)
	{
		

		//running
		if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == FORWARDS) {
			m_RigidBody->ApplyForceX(m_Speed * FORWARDS);
			m_IsFacingRight = true;
			m_isRunning = true;

		}
		if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == BACKWARDS) {
			m_RigidBody->ApplyForceX(m_Speed * BACKWARDS);
			m_IsFacingRight = false;
			m_isRunning = true;
		}



		//Crouch 
		if (Input::GetInstance()->GetAxisKey(VERTICAL) == UPWARDS && m_IsGrounded) {
			m_IsCrouching = true;
			m_RigidBody->UnSetForce();
			//m_Collider->SetBuffer(0, 0, 0, 20);
		}


		//fireball Mario
		//FireStyle: Great FireBall Jutsu
		if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_LSHIFT))
		{

		}

		//JUMP
		if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_IsGrounded)
		{
			m_IsJumping = true;
			m_IsGrounded = false;
			m_RigidBody->ApplyForceY(UPWARDS * m_JumpForce);

		}
		if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_IsJumping && m_JumpTime > 0)
		{
			m_JumpTime -= deltaTime;
			m_RigidBody->ApplyForceY(UPWARDS * m_JumpForce);
		}
		else
		{
			m_IsJumping = false;
			m_JumpTime = JUMP_TIME;
		}

		//fall
		if (m_RigidBody->Velocity().Y > 0 && !m_IsGrounded) // when the player starts falling that means the velocity is greater than 0// when you jump the velocity is acc less than 0 and when you fall the velocity is greater than 0
		{//also the player must not be grounded
			m_isFalling = true;
		}
		else
		{
			m_isFalling = false;
		}

	}

		//move on x axis
		m_RigidBody->Update(deltaTime);// we update our rb position because it inherit the positiion that the transform of our player should have. We calculate the position using the rigid body and we use that rb position to update ourtransform
		m_lastSafePosition.X = m_Transform->X;// before we cllide with anything we take our current position on the X-axis and store it inside the last position before we move the rb position
		m_Transform->X += m_RigidBody->Position().X;//
		m_Collider->Set(m_Transform->X, m_Transform->Y, 30, 64);
		if (Collisions::Instance()->MapCollision(m_Collider->Get()))
		{
			m_Transform->X = m_lastSafePosition.X;
		}

		//move on the Y axis
		m_RigidBody->Update(deltaTime);
		m_lastSafePosition.Y = m_Transform->Y;
		m_Transform->Y += m_RigidBody->Position().Y;
		m_Collider->Set(m_Transform->X, m_Transform->Y, 30, 64);
		if (Collisions::Instance()->MapCollision(m_Collider->Get()))
		{
			m_IsGrounded = true;
			m_Transform->Y = m_lastSafePosition.Y;
		}
		else
		{
			m_IsGrounded = false;
		}


	// wee need to set the transform of the value of the player using rigidbody. then we apply the value the rigidbody has to the player
	//m_Transform->TranslateX(m_RigidBody->Position().X);
	//m_Transform->TranslateY(m_RigidBody->Position().Y);

	m_Origin->X = m_Transform->X + m_Width / 2;//calculates the origin of the player
	m_Origin->Y = m_Transform->Y + m_Height / 2;
	facingDir = m_IsFacingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
	AnimState();

	m_Animation->Update(deltaTime);

	//Character::Update(deltaTime);
}


void CharacterMario::AnimState() {
	//idling
	m_Animation->SetProps("playerIdle", 0, 1, 100, facingDir);// idle anim

	//running
	if (m_isRunning)
		m_Animation->SetProps("playerRun", 0, 3, 100, facingDir);//run right anim

	//gliding


	//crouching


	//jumping
	if (m_IsJumping)
		m_Animation->SetProps("playerJump", 0, 1, 100, facingDir);


	//falling
	if (m_isFalling)
		m_Animation->SetProps("playerJump", 0, 1, 100, facingDir);

	//Attacking



}
void CharacterMario::Clean() {
	TextureAnim::GetInstance()->Clean();
}

CharacterMario::~CharacterMario() {
	delete m_RigidBody;
	m_RigidBody = nullptr;
	delete m_Animation;
	m_Animation = nullptr;
	delete m_Collider;
	m_Collider = nullptr;
	//TextureAnim::GetInstance()->Clean();
}
