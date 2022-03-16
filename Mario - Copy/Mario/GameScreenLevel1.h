#pragma once
#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "Collisions.h"
#include "LevelMap.h"
#include "Coins.h"
#include "POWblock.h"
#include "CharacterKoopa.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>




class Texture2D;
class POWblock;
class CharacterMario;
class CharacterLuigi;
class CharacterKoopa;
class GameScreenLevel1 : public GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime) override;
	void Clean();
	//inline LevelMap* GetMap() { return m_LevelMap; }
	void UpdatePowBlock();

private:
	//texts
	void ArrayTxt();
	Texture2D* m_background_texture;
	TextManager* m_LevelUI;
	TextManager* m_LevelIntUI;
	string m_UInamesArr[5];
	string m_UIints[5];
	Vector2D m_UIPos[5];
	TTF_Font* font;
	Colours COLOUR;
	SDL_Surface* textSurface;
	SDL_Texture* texture;
	SDL_Rect textRect;
	
	//UI
	int m_Coins, m_Level, m_Time, m_Lives;
	int m_CoinCount;
	int frameCount;
	bool m_levelComplete;
	bool m_LevelFailed;

	//objects
	bool SetUpLevel();
	bool m_CanCollide;
	CharacterMario* Mario;
	Coins* coins;
	vector <Coins*> m_CoinsObj;
	vector<CharacterKoopa*> m_enemies;
	//CharacterLuigi* Luigi;
	CharacterKoopa* koopa;
	void SetLevelMap();
	LevelMap* m_level_map;
	POWblock* m_pow_block;


	//level variables
	void UpdateEnemies(float deltaTime);
	void CreateKoopa(int x, int y);
	float koopaSwpawner; //countdown to spawn koopa

	

	
	//screeen
	LevelMap* m_LevelMap;
	Vector2D* background;
	bool m_screenShake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;
	
	void DoScreenshake();


};
