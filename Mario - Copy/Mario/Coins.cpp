#include "Coins.h"




Coins::Coins(Properties* props) : Character(props)
{
	m_Collider = new Collider();
	//m_Collider->Set(m_Transform->X, m_Transform->Y, 16, 22);
	m_Collider->SetBuffer(0,0,0,0);


	m_Animation = new Animation();
	m_Animation->SetProps(m_TextureID, 0, 3, 100, SDL_FLIP_NONE);
	m_collisionRadius = 11;
}


void Coins::Render() {
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
	Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect box = { (int)(m_Collider->Get().x -cam.X),(int)(m_Collider->Get().y - cam.Y), m_Collider->Get().w,m_Collider->Get().h };
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}


void Coins::Update(float deltaTime) {

	//m_Animation->SetProps("Coins", 0, 3, 100, SDL_FLIP_NONE);

	
	m_Animation->Update(deltaTime);

}

void Coins::Clean(string s) {

	TextureAnim::GetInstance()->Drop("Coins"+s);
}

Coins::~Coins()
{
	delete m_Animation;
	m_Animation = nullptr;
	delete m_Collider;
	m_Collider = nullptr;
}
