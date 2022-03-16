#include "Texture2D.h"
#include "SDL_image.h"
#include <iostream>
using namespace std;



Texture2D::Texture2D(SDL_Renderer* renderer) {
	m_renderer = renderer;
}

Texture2D::~Texture2D() {
	Free();
	m_renderer = nullptr;
}

void Texture2D::Renderer(Vector2D* new_position, SDL_RendererFlip flip, double angle) {

	SDL_Rect renderLocation = { new_position->X,new_position->Y,m_width,m_height };
	SDL_RenderCopyEx(m_renderer, m_texture, NULL, &renderLocation, 0, NULL, flip);
}


void Texture2D::Renderer(SDL_Rect src_rect, SDL_Rect src_dest, SDL_RendererFlip flip, double angle) {
	SDL_RenderCopyEx(m_renderer, m_texture, &src_rect, &src_dest, angle, nullptr, flip);
}

void Texture2D::Draw(Vector2D* position, SDL_RendererFlip flip ) {
	SDL_Rect renderLocation = { position->X,position->Y,m_width,m_height };
	SDL_RenderCopy(m_renderer, m_texture, &renderLocation, NULL);
}

bool Texture2D::LoadTextureFromFile(string path) {
	//remove memory used for a previous texture
	Free();

	

	//Load the image
	SDL_Surface* p_surface = IMG_Load(path.c_str());
	if (p_surface != nullptr) {
		SDL_SetColorKey(p_surface, SDL_TRUE, SDL_MapRGB(p_surface->format, 0, 0xFF, 0xFF));
		//CREATE THE TEXTURE FROM THE PIXEL ON YOU SURFACE
		m_texture = SDL_CreateTextureFromSurface(m_renderer, p_surface);
		if (m_texture == nullptr) {
			SDL_Log("Unable to create texture from Surface. Error %s\n", SDL_GetError());
		}
		else
		{
			m_width = p_surface->w;
			m_height = p_surface->h;
		}
		//remove the loaded surface now that we have a texture
		SDL_FreeSurface(p_surface);
	}
	else {
		SDL_Log("Unable to create texture from surface. Error %s\n", IMG_GetError());
	}

	//return whether the process was successful
	return m_texture != nullptr;
}


void Texture2D::Free() {

	//check if texture exisys before removing it
	if (m_texture != nullptr) {
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
		m_width = 0;
		m_height = 0;
	}

}