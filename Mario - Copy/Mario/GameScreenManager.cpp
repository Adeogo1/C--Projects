#include "GameScreenManager.h"
#include "GameScreenIntro.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "GameScreenLevels.h"
#include "GameScreenFinished.h"

GameScreenManager* GameScreenManager::m_sInstance = nullptr;

GameScreenManager::GameScreenManager() {


}

void GameScreenManager::Init(SDL_Renderer* renderer, SCREENS startScreen) {
	m_renderer = renderer;
	m_current_screen = nullptr;
	ChangeScreens(startScreen);
}


void GameScreenManager::Render() {
	m_current_screen->Render();

}

void GameScreenManager::Update(float deltaTime) {

	m_current_screen->Update(deltaTime);
}

void GameScreenManager::ChangeScreens(SCREENS new_screen, int level) {
	if (m_current_screen != nullptr) {
		delete m_current_screen;
	}
	GameScreen* tempScreen;//;GameScreenLevel1* tempScreen;
	switch (new_screen)
	{
	case SCREEN_INTRO:
		tempScreen = new GameScreenIntro(m_renderer);
		m_current_screen = (GameScreen*)tempScreen;
		tempScreen = nullptr;
		break;
	case SCREEN_LEVELSELECT:
		tempScreen = new GameScreenLevels(m_renderer);
		m_current_screen = (GameScreen*)tempScreen;
		tempScreen = nullptr;
		break;//wait 
	case SCREEN_LEVEL1:
		m_level = 1;
		tempScreen = new GameScreenLevel1(m_renderer);
		m_current_screen = (GameScreen*)tempScreen;
		tempScreen = nullptr;
		break;//wait 
	case SCREEN_LEVEL2:
		m_level = 2;
		tempScreen = new GameScreenLevel2(m_renderer);
		m_current_screen = (GameScreen*)tempScreen;
		tempScreen = nullptr;
		break;//wait 
	case SCREEN_GAMEOVER:
		tempScreen = new GameScreenFinished(m_renderer, false, level);
		m_current_screen = (GameScreen*)tempScreen;
		tempScreen = nullptr;
		break;//wai
	case SCREEN_LEVELCOMPLETE:
		tempScreen = new GameScreenFinished(m_renderer, true, level);
		m_current_screen = (GameScreen*)tempScreen;
		tempScreen = nullptr;
		break;//wait 

	default:
		break;
	}
}

void GameScreenManager::Clean() {

}

GameScreenManager::~GameScreenManager() {
	m_renderer = nullptr;
	delete menu;
	menu = nullptr;
	delete m_current_screen;
	m_current_screen = nullptr;
}
