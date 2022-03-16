#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <iostream>
using namespace std;

class Collider
{
public:
	inline SDL_Rect Get() { return m_Box; }
	inline void SetBuffer(int x, int y, int w, int h) { m_Buffer = { x,y,w,h }; }

	void Set(int x, int y, int w, int h) {// when you want to set the value of the collider we alway want to remove the buffer from that
		m_Box = { x - m_Buffer.x,y - m_Buffer.y,w - m_Buffer.w,h - m_Buffer.h };
	}


	Collider() {}
	~Collider() {}

private:
	SDL_Rect m_Box;
	SDL_Rect m_Buffer;// the size of the image is usually greater than the size of the character
};
