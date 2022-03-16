#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "TextureAnim.h"
#include <iostream>
#include <map>
using namespace std;





class Animation
{
public:
	//Animation(bool repeat = true) : m_Repeat(repeat) { m_IsEnded = false; }
	Animation();
	void Update(float deltaTime);
	void Draw(float x, float y, int spriteWidth, int spriteHeight);
	void SetProps(string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//inline bool IsEnded() { return m_IsEnded; }

	~Animation();

protected:
	//bool m_Repeat;//makes sure the animation will keep looping forever
	//bool m_IsEnded;// tels us if the animation is finished
	//int m_CurrentFrame;
	int m_SpriteRow, m_SpriteFrame, m_AnimSpeed, m_FrameCount;
	string m_TextureID;
	SDL_RendererFlip m_Flip;
};


