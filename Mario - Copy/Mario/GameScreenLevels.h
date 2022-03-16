#pragma once
#include "GameScreen.h"




class GameScreenLevels: public GameScreen
{
public:
	GameScreenLevels(SDL_Renderer* renderer);
	virtual void Update(float deltaTime);
	void Render() override;
	void Clean();

	~GameScreenLevels();

private:
	bool SetUpLevel();
	Texture2D* m_background_texture;
	TTF_Font* font;
	Colours COLOUR;
	SDL_Surface* textSurface;
	SDL_Texture* texture;
	SDL_Rect textRect;
	Vector2D m_ButtonPositions[3];
	string m_ButtonName[3];
	//TextureAnim* m_pointer;
	Vector2D* bg;
	Texture2D* m_pointer;
	int u;
	TextManager* m_Menu;
	bool keyDown;
	
};


