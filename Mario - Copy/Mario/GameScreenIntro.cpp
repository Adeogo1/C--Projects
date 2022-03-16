#include "GameScreenIntro.h"






GameScreenIntro::GameScreenIntro(SDL_Renderer* renderer) : GameScreen(renderer)
{
	//screen = nullptr;

	bg = new Vector2D(0, 0);
	m_ButtonName[0] = "Start";
	m_ButtonName[1] = "Level Select";
	m_ButtonName[2] = "HighScore";
	m_ButtonName[3] = "Exit";
	
	for (int i = 0; i < 4; i++)
	{
		m_ButtonPositions[i].X = 110;
		if (i == 0)
		{
			m_ButtonPositions[i].Y =  80;
		}
		else
		{
			m_ButtonPositions[i].Y = ((i) * 150)+80;
		}
		
	}
	m_Menu = new TextManager(m_renderer,textSurface,texture, 45, "Freedom-10eM.ttf", font);

	TextureAnim::GetInstance()->LoadTexture("Bg", "Images/MarioPointing1pt2.png");

	SetUpLevel();


}



void GameScreenIntro::Render() {


	m_background_texture->Renderer(bg, SDL_FLIP_NONE);
	//m_pointer->Renderer(Vector2D(-35,20), SDL_FLIP_NONE);
	TextureAnim::GetInstance()->Draw("Bg", -35, m_ButtonPositions[j].Y - 50, 170, 195);
	for (int i = 0; i < 4; i++)
	{
		textRect.x = m_ButtonPositions[i].X;
		textRect.y = m_ButtonPositions[i].Y;
		textRect.h = 60;
		textRect.w = 200;
		m_Menu->DrawText(textRect.x,textRect.y, textRect.w, textRect.h, m_ButtonName[i], COLOUR.GREEN);
		m_Menu->Renderer();
	}

	
}




void GameScreenIntro::Update(float deltaTime) {

	bool changingScreens = true;

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_1)) {

		j = 0;

	}
	else if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_2)) {
		j = 1;
	}
	else if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_3)) {
		j = 2;
	}
	else if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_4)) {
		j = 3;
	}

	if (j == 0 && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN)) {
		GameScreenManager::GetInstance()->ChangeScreens(SCREEN_LEVEL1);
	}
	else if (j == 1 && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN)) {
		GameScreenManager::GetInstance()->ChangeScreens(SCREEN_LEVELSELECT);
		
	}
	else if (j == 2 && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN)) {
		GameScreenManager::GetInstance()->ChangeScreens(SCREEN_HIGHSCORES);
	}
	else if (j == 3 && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN)) {
		Engine::GetInstance()->Quit();
	}

}

int GameScreenIntro::GetPointerPos()
{
	return j; 
}



bool GameScreenIntro::SetUpLevel() {
	m_background_texture = new Texture2D(m_renderer);
	//m_pointer = new Texture2D(m_renderer);
	//if (!m_background_texture->LoadTextureFromFile("Images/BackgroundMB.png")) {
	//	cout << "Failed to load background texture!" << endl;
	//	return false;
	//}
	if (!m_background_texture->LoadTextureFromFile("Images/MarioMenu6.png")) {
		cout << "Failed to load background texture!" << endl;
		return false;
	}
	//if (!m_pointer->LoadTextureFromFile("Images/MarioPointing1pt2.png")) {
	//	cout << "Failed to load background texture!" << endl;
	//	return false;
	//}

	return true;
}

void GameScreenIntro::Clean() {
	TextureAnim::GetInstance()->Clean();
}


GameScreenIntro::~GameScreenIntro() {
	delete m_background_texture;
	delete font;
	font = nullptr;
	delete textSurface;
	textSurface = nullptr;
	delete texture;
	texture = nullptr;
	delete bg;
	bg = nullptr;
	delete m_pointer;
	m_pointer = nullptr;
	delete m_Menu;
	m_Menu = nullptr;



}