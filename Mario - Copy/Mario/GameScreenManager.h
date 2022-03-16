#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include"Commons.h"
//#include "GameScreenLevels.h"



class GameScreen;
class GameScreenIntro;
class GameScreenLevels;
class GameScreenFinished;
class GameScreenManager
{
public:

	
	~GameScreenManager();

	void Render();
	void Update(float deltaTime);
	void Clean();

	static GameScreenManager* GetInstance() {
		return m_sInstance = (m_sInstance != nullptr) ? m_sInstance : new GameScreenManager();
	}
	void Init(SDL_Renderer* renderer, SCREENS startScreen);
	void ChangeScreens(SCREENS new_screen, int level = 0);
	int GetLevel() { return m_level; }


private:
	
	GameScreenManager();
	SDL_Renderer* m_renderer;
	GameScreen* m_current_screen;
	GameScreenIntro* menu;
	
	static GameScreenManager* m_sInstance;
	int m_level;
	bool m_menuScreen = true;
	bool m_HighScoreScreen = false;
	bool m_startScreen = false;
};



