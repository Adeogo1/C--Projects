#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "Engine.h"
#include "Constants.h"
#include "Texture2D.h"
#include "Character.h"
#include "CharacterMario.h"
#include "GameScreenManager.h"
#include "Commons.h"
#include <iostream>
using namespace std;




Uint32 g_old_time;
//GameScreenManager* game_screen_manager;
Mix_Music* g_music = nullptr;
void LoadMusic(string filePath);
int main(int argc, char* args[]) {


		LoadMusic("Music/Mario.mp3");
		if (Mix_PlayingMusic() == 0) {
			Mix_PlayMusic(g_music, -1);
		}

		Engine::GetInstance()->Init();
		
		while (Engine::GetInstance()->IsRunning())// game loop
		{
			Engine::GetInstance()->Events();
			Engine::GetInstance()->Update();// where we do everything
			Engine::GetInstance()->Render();// contains everything that will be drawn on screen
			Timer::GetInstance()->Tick();
		}

		Engine::GetInstance()->Clean(); // if the player decided to quit or kill the game engine, we need to clean the game engine to make sure there is no texture and pointers in the memory


	return 0;


}





void LoadMusic(string filePath) {
	g_music = Mix_LoadMUS(filePath.c_str());
	if (g_music == nullptr)
	{
		cout << "Failed to Load music. Error " << Mix_GetError() << endl;
	}
}
















