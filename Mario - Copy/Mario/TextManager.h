#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;



class TextManager
{
public:
	TextManager(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, int size, string text, TTF_Font* font);

	void Update();
	void Renderer();
	void DrawText(int x, int y,int width, int height ,string text, SDL_Color colour);// this is for the text info 
	~TextManager();

private:
	SDL_Renderer* m_Renderer;
	int m_FontSize;
	string m_Text;
	TTF_Font* m_font;
	SDL_Surface* m_textSurface;
	SDL_Texture* m_texture;
	SDL_Rect m_textRect;
	SDL_Color m_colour;
};


