#pragma once
#ifndef _TEXTURE2D_H
#define _TEXTURE2D_H
#include "SDL.h"
#include <string>
#include "Commons.h"
#include "Vector2D.h"
using namespace std;



class Texture2D
{
public:
	Texture2D(SDL_Renderer* renderer);
	~Texture2D();

	void Renderer(Vector2D* new_position, SDL_RendererFlip flip, double angle = 0.0);
	void Renderer(SDL_Rect src_rect, SDL_Rect src_dest, SDL_RendererFlip flip, double angle = 0.0);
	void Draw(Vector2D* position, SDL_RendererFlip flip = SDL_FLIP_NONE);
	bool LoadTextureFromFile(string path);
	void Free();

	int GetWidth() { return m_width;  }
	int GetHeight() { return m_height;  }

	SDL_Texture* GetTexture() { return m_texture; }

private:
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture = nullptr;

	int m_width;
	int m_height;

};



#endif //_TEXTURE2D_H