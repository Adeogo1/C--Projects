#pragma once
#include "GameScreen.h"
#include "GameScreenManager.h"
#include "SDL_ttf.h"





class GameScreenIntro : public GameScreen
{
public:
	GameScreenIntro(SDL_Renderer* renderer);
	~GameScreenIntro();

	void Render() override;
	void Update(float deltaTime) override;
	void Clean();
	int GetPointerPos();

private:
	//GameScreenManager* screen;
	bool SetUpLevel();
	Texture2D* m_background_texture;
	TTF_Font* font;
	Colours COLOUR;
	SDL_Surface* textSurface;
	SDL_Texture* texture;
	SDL_Rect textRect;
	Vector2D m_ButtonPositions[4];
	string m_ButtonName[4];
	//TextureAnim* m_pointer;
	Vector2D* bg;
	Texture2D* m_pointer;
	int j;
	TextManager* m_Menu;
};
