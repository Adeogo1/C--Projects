#pragma once
#include "GameScreen.h"





class GameScreenFinished : public GameScreen
{
public:
	GameScreenFinished(SDL_Renderer* renderer, bool LevelComplete, int level);
	~GameScreenFinished();

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
	//TextureAnim* m_pointer;
	Vector2D* bg;
	Texture2D* m_pointer;
	int j;
	TextManager* m_Menu;
	bool m_LevelState;
	int level;
};
