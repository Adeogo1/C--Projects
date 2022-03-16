#pragma once
#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "Constants.h"
#include "Texture2D.h"
#include "TextManager.h"
#include "TextureAnim.h"
#include "Input.h"
#include "Commons.h"
#include <iostream>
using namespace std;



class GameScreen
{
public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();
	int GetLevelChoice() { return levelChoice; }
	virtual void Render();
	virtual void Update(float deltaTime);
private:
	

protected:
	SDL_Renderer* m_renderer;
	int m_Score;
	int levelChoice = 0;
};


#endif // !_GAMESCREEN_H