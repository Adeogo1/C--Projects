#include "GameScreenLevels.h"

GameScreenLevels::GameScreenLevels(SDL_Renderer* renderer) : GameScreen(renderer)
{
	//screen = nullptr;

	bg = new Vector2D(0, 0);

	m_ButtonName[0] = "Level 1";
	m_ButtonName[1] = "Level 2";
	m_ButtonName[2] = "Back";


	keyDown = true;


	for (int i = 0; i < 3; i++)
	{
		m_ButtonPositions[i].X = 110;
		if (i == 0)
		{
			m_ButtonPositions[i].Y = 80;
		}
		else
		{
			m_ButtonPositions[i].Y = ((i) * 150) + 80;
		}

	}
	m_Menu = new TextManager(m_renderer, textSurface, texture, 45, "Freedom-10eM.ttf", font);

	TextureAnim::GetInstance()->LoadTexture("Bg", "Images/MarioPointing1pt2.png");

	SetUpLevel();


}



void GameScreenLevels::Render() {

	
	bg->X = 0;
	bg->Y = 0;
	m_background_texture->Renderer(bg, SDL_FLIP_NONE);
	//m_pointer->Renderer(Vector2D(-35,20), SDL_FLIP_NONE);
	TextureAnim::GetInstance()->Draw("Bg", -35, m_ButtonPositions[u].Y - 50, 170, 195);
	for (int i = 0; i < 3; i++)
	{
		textRect.x = m_ButtonPositions[i].X;
		textRect.y = m_ButtonPositions[i].Y;
		textRect.h = 60;
		textRect.w = 200;
		m_Menu->DrawText(textRect.x, textRect.y, textRect.w, textRect.h, m_ButtonName[i], COLOUR.GREEN);
		m_Menu->Renderer();
	}


}


void GameScreenLevels::Clean() {

}

void GameScreenLevels::Update(float deltaTime) {

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_1)) {

		u = 0;
		levelChoice = 0;
	}
	else if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_2)) {
		u = 1;
		levelChoice = 1;
	}
	else if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_3)) {
		u = 2;
	}

	if (u == 0 && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RIGHT) ) {
		GameScreenManager::GetInstance()->ChangeScreens(SCREEN_LEVEL1);
	}
	else if (u == 1 && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RIGHT)) {
		GameScreenManager::GetInstance()->ChangeScreens(SCREEN_LEVEL2);
	}
	else if (u == 2 && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RIGHT)) {
		GameScreenManager::GetInstance()->ChangeScreens(SCREEN_INTRO);
	}
}





bool GameScreenLevels::SetUpLevel() {
	m_background_texture = new Texture2D(m_renderer);

	if (!m_background_texture->LoadTextureFromFile("Images/MarioMenu6.png")) {
		cout << "Failed to load background texture!" << endl;
		return false;
	}


	return true;
}


GameScreenLevels::~GameScreenLevels() {
	m_background_texture = nullptr;
	//SDL_DestroyTexture(text);
	//text = nullptr;
}
