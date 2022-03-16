#include "GameScreenFinished.h"





GameScreenFinished::GameScreenFinished(SDL_Renderer* renderer, bool levelComplete, int level) : GameScreen(renderer)
{
	bg = new Vector2D(0, 0);

	m_LevelState = levelComplete;


	m_Menu = new TextManager(m_renderer, textSurface, texture, 45, "Freedom-10eM.ttf", font);


	SetUpLevel();
}

void GameScreenFinished::Render() {


	m_background_texture->Renderer(bg, SDL_FLIP_NONE);


	m_Menu->DrawText(textRect.x, 600, textRect.w, textRect.h, "Press enter to go to the next level", COLOUR.RED);
	m_Menu->Renderer();



}




void GameScreenFinished::Update(float deltaTime) {

	if (m_LevelState == true)
	{
		if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN))
		{
			GameScreenManager::GetInstance()->ChangeScreens(SCREEN_LEVELSELECT);
		}
	}
	else
	{
		if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN))
		{
			GameScreenManager::GetInstance()->ChangeScreens(SCREEN_LEVEL1);
		}
	}

}

int GameScreenFinished::GetPointerPos()
{
	return 1;
}



bool GameScreenFinished::SetUpLevel() {
	if (m_LevelState == true)
	{
		m_background_texture = new Texture2D(m_renderer);

		if (!m_background_texture->LoadTextureFromFile("Images/GameComplete.jpg")) {
			cout << "Failed to load background texture!" << endl;
			return false;
		}
	}
	else
	{
		m_background_texture = new Texture2D(m_renderer);

		if (!m_background_texture->LoadTextureFromFile("Images/gameover.jpg")) {
			cout << "Failed to load background texture!" << endl;
			return false;
		}
	}



	return true;
}

void GameScreenFinished::Clean() {

}

GameScreenFinished::~GameScreenFinished()
{
}

