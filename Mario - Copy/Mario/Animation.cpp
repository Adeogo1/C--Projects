#include "Animation.h"




Animation::Animation()
{
}

void Animation::Update(float deltaTime) {
	m_SpriteFrame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;
}



void Animation::Draw(float x, float y, int spriteWidth, int spriteHeight) {
	TextureAnim::GetInstance()->DrawFrame(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_SpriteFrame, m_Flip);
}

void Animation::SetProps(string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip) {
	m_TextureID = textureID;
	m_SpriteRow = spriteRow;
	m_FrameCount = frameCount;
	m_AnimSpeed = animSpeed;
	m_Flip = flip;


}

Animation::~Animation()
{
}