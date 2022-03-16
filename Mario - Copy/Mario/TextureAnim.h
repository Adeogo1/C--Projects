#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "Constants.h"
#include "Camera.h"
#include <iostream>
#include <map>
using namespace std;






class TextureAnim
{
public:

	static TextureAnim* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextureAnim();
	}

	bool LoadTexture(string id, string filename);
	//bool ParseTexture(string source);// dont include this
	void Drop(string id);//when you want to remove a texture from the map
	void Clean();	//when we finished what we need to do we need to clean all the textures from the memory
	void Delete(string id);

	void Draw(string ID, int x, int y, int width, int height, float scaleX = 1, float scaleY = 1, float scrollRatio = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);//function to draw static object 
	void DrawTile(string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DrawFrame(string ID, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);//function to draw animations
	int GetWidth();
	int GetHeight();
	~TextureAnim();

private:
	TextureAnim() {}
	map<string, SDL_Texture*> m_TextureMap;
	static TextureAnim* s_Instance;
	int m_width;
	int m_height;

};
