#include "TextureAnim.h"
#include "Engine.h"





TextureAnim* TextureAnim::s_Instance = nullptr;


bool TextureAnim::LoadTexture(string id, string filename) {
	SDL_Surface* surface = IMG_Load(filename.c_str());	//to load a texture or any texture you need to use a surface, IMG LOAD is a function from the sdl image library which simply load an image and turns it to a surface it takes a char so convert your string to a char
	//loaded the image and turned it into a surface
	if (surface == nullptr)
	{
		SDL_Log("failed to Load Texture SDL: %s, %s", filename.c_str(), SDL_GetError());
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
	if (texture == nullptr) {
		SDL_Log("failed to Load Texture from surface: %s", SDL_GetError());
		return false;
	}

	m_TextureMap[id] = texture;
	SDL_FreeSurface(surface);
	return true;

}



void TextureAnim::Draw(string ID, int x, int y, int width, int height, float scaleX, float scaleY, float scrollRatio, SDL_RendererFlip flip) {
	SDL_Rect srcRect = { 0,0,width,height };	// you define which part of the image will be showing on the screen, the source is the part of the image we want to show on the screen and the destination is where on the screen we want to show this
	Vector2D cam = Camera::GetInstance()->GetPosition() * scrollRatio;//PARALLAX EFFECT
	SDL_Rect desRect = { x - cam.X, y - cam.Y, width * scaleX, height * scaleY };
	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[ID], &srcRect, &desRect, 0.0, nullptr, flip);

}


void TextureAnim::DrawTile(string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip) {
	SDL_Rect srcRect = { tileSize * frame,tileSize * row,tileSize,tileSize };
	Vector2D cam = Camera::GetInstance()->GetPosition();		//calculationg the destination rect according to the camera position
	SDL_Rect dstRect = { x - cam.X,y - cam.Y,tileSize,tileSize };

	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[tilesetID], &srcRect, &dstRect, 0, 0, flip);

}


void TextureAnim::DrawFrame(string ID, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip) {
	SDL_Rect srcRect = { width * frame, height * row, width, height };
	m_width = width;
	m_height = height;
	Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect desRect = { x - cam.X, y - cam.Y, width, height };
	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[ID], &srcRect, &desRect, 0.0, nullptr, flip);
}


void TextureAnim::Drop(string id) {//removes texture from our texture map that we created
	SDL_DestroyTexture(m_TextureMap[id]);//destroys it but doesnt remove it from our map
	m_TextureMap.erase(id);

}

void TextureAnim::Delete(string id) {
	if (m_TextureMap[id] != nullptr) {
		SDL_DestroyTexture((m_TextureMap[id]));
		m_TextureMap[id] = nullptr;
		m_width = 0;
		m_height = 0;
	}
}


int TextureAnim::GetWidth() {
	return m_width;
}

int TextureAnim::GetHeight() {
	return m_height;
}

void TextureAnim::Clean() {
	map<string, SDL_Texture*>::iterator it;
	for (it = m_TextureMap.begin(); it != m_TextureMap.end(); it++)
	{
		SDL_DestroyTexture(it->second);
	}
	m_TextureMap.clear();
	SDL_Log("Texture Map clean");
}


TextureAnim::~TextureAnim()
{
}