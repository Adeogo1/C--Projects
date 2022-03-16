#include "TextManager.h"





TextManager::TextManager(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture, int size, string text, TTF_Font* font)
{
	if (TTF_Init() < 0)
	{
		cout << "Error: " << TTF_GetError() << endl;
	}

	m_Renderer = renderer;
	m_FontSize = size;
	m_Text = text;
	m_font = font;
	m_textSurface = surface;
	m_texture = texture;
	m_font = TTF_OpenFont(m_Text.c_str(), m_FontSize);
	if (m_font == nullptr)
		cout << " Failed to load font : " << SDL_GetError() << endl;

	

	



}

void TextManager::Update() {
	Renderer();
}



void TextManager::Renderer() {

	
	SDL_RenderCopy(m_Renderer, m_texture, NULL, &m_textRect);

}


void TextManager::DrawText(int x, int y, int width, int height, string text, SDL_Color colour) {
	
	m_textRect.x = x;
	m_textRect.y = y;
	m_textRect.w = width;
	m_textRect.h = height;
	
	m_textSurface = TTF_RenderText_Solid(m_font, (char*)text.c_str(), colour);
	m_texture = SDL_CreateTextureFromSurface(m_Renderer, m_textSurface);
	SDL_QueryTexture(m_texture, NULL, NULL, &m_textRect.w, &m_textRect.h);
}

//void TextManager::DrawTextInt(int x, int y, int width, int height, int num, SDL_Color colour) {
//	
//	m_textRect.x = x;
//	m_textRect.y = y;
//	m_textRect.w = width;
//	m_textRect.h = height;
//	stringstream s;
//	ss.str()
//
//	m_textSurface = TTF_RenderText_Solid(m_font, intStr, colour);
//	m_texture = SDL_CreateTextureFromSurface(m_Renderer, m_textSurface);
//	SDL_QueryTexture(m_texture, NULL, NULL, &m_textRect.w, &m_textRect.h);
//}


TextManager::~TextManager()
{
	//SDL_FreeSurface(surface);
	//surface = nullptr;
}
