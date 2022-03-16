#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "Input.h"
#include "GameScreenManager.h"
#include "CharacterMario.h"
#include "Camera.h"
#include "Timer.h"
#include "CharacterKoopa.h"
#include "Constants.h"
#include "TextureAnim.h"
#include "MapParser.h"
#include <iostream>
using namespace std;





class Engine
{
public:


	static Engine* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();//we will always have one instance of this class so whenever we refernce this anywhere in the code we will always come back to this
	}
	// gives us access to the object

	bool Init();
	bool Clean();
	void Quit();

	void Update();
	void Render();
	void Events();
	virtual ~Engine();

	void InitMap(string ID, int level);
	void UpdateMap();
	void RenderMap();
	void CleanMap();

	void InitMap2(string ID, int level);
	void UpdateMap2();
	void RenderMap2();
	void CleanMap2();


	inline LevelMap* GetMap() { return m_LevelMap; }// returns vector of layers
	inline LevelMap* GetMap2() { return m_LevelMap2; }// returns vector of layers


	inline bool IsRunning() //optimise the compiler. whenever i call this function it will m_IsRunning this value and paste it in the place where its called
	{
		return m_IsRunning;
	}
	inline SDL_Renderer* GetRenderer() {
		return m_Renderer;
	}

private:
	Engine() {}// the constructor should be private because anyone can create a new instance of it
	static Engine* s_Instance;//we want to have only one instance of the engine in the whole program and we dont want to create another hence why we make it singleton
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	//GameScreenManager* game_screen_manager;
	Uint32 g_old_time;
	Mix_Music* g_music = nullptr;



	LevelMap* m_LevelMap;
	LevelMap* m_LevelMap2;
	bool m_IsRunning;

};

