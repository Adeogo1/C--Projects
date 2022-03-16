#include "Engine.h"



Engine* Engine::s_Instance = nullptr;//initialise
CharacterMario* Mario;
//GameObject* Mario;

bool Engine::Init() {

	
	if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
	{
		SDL_Log("failed to initialise SDL: %s", SDL_GetError());
		return false;
	}
	m_Window = SDL_CreateWindow("Adeeee", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (m_Window == nullptr)// if the window wasnt initialised
	{
		SDL_Log("failed to Create Window: %s", SDL_GetError());
		return false;
	}
	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);// the 3rd parameter is how the renderer should work, should it be synchronized with the frequence of our system or not. - the values in the third parameter means that we are snchronising it with the frame rate of our screen
	if (m_Renderer == nullptr)
	{
		SDL_Log("failed to Create Renderer: %s", SDL_GetError());
		return false;
	}
	

	//if (!MapParser::GetInstance()->Load())
	//{
	//	cout << "Failed to load map" << endl;
	//}

	//m_LevelMap = MapParser::GetInstance()->GetMap("Level1");
	//m_LevelMap2 =  MapParser::GetInstance()->GetMap("Level2");

	//small mario
	//TextureAnim::GetInstance()->LoadTexture("smallPlayerIdle", "Images/MarioSpritesheet/SmallMario.png");
	//TextureAnim::GetInstance()->LoadTexture("playerIdle", "Images/MarioSpritesheet/BigMarioIdle.png");
	//TextureAnim::GetInstance()->LoadTexture("playerRun", "Images/MarioSpritesheet/BigMarioRun(2).png");
	//TextureAnim::GetInstance()->LoadTexture("playerJump", "Images/MarioSpritesheet/BigMarioJump.png");
	//TextureAnim::GetInstance()->LoadTexture("Bg", "Images/back.png");
	//Mario = new CharacterMario(new Properties("playerIdle", 0, 0, 30, 69));


	//extureAnim::GetInstance()->LoadTexture("EnemyMoving", "Images/MarioSpritesheet/Koopa.png");
	//CharacterKoopa* koopa = new CharacterKoopa(new Properties("EnemyMoving", 0, 0, 30, 30));

	//Camera::GetInstance()->SetTarget(Mario->GetOrigin());
	/*game_screen_manager = new GameScreenManager(m_Renderer, SCREEN_INTRO);*/
	GameScreenManager::GetInstance()->Init(m_Renderer, SCREEN_INTRO);
	g_old_time = SDL_GetTicks();

	return m_IsRunning = true;

}


bool Engine::Clean() {

	TextureAnim::GetInstance()->Clean();
	SDL_DestroyWindow(m_Window);
	SDL_DestroyRenderer(m_Renderer);
	IMG_Quit();
	SDL_Quit();
	return true;
}




void Engine::Update() {
	Uint32 new_time = SDL_GetTicks();
	float deltaTime = Timer::GetInstance()->GetDeltaTime();
	//game_screen_manager->Update(deltaTime);
	GameScreenManager::GetInstance()->Update(deltaTime);
	g_old_time = new_time;
	//Camera::GetInstance()->Update((float)(new_time - g_old_time) / 1000.0f);
	//m_LevelMap->Update();

	//Mario->Update((float)(new_time - g_old_time) / 1000.0f);
}




void Engine::Render() {
	SDL_SetRenderDrawColor(m_Renderer, 67, 0, 111, 255);
	SDL_RenderClear(m_Renderer);//you need to clear the render before you render it

	//game_screen_manager->Render();
	GameScreenManager::GetInstance()->Render();
	SDL_RenderPresent(m_Renderer);//presents the renderer
}

void Engine::Events() {
	Input::GetInstance()->Listen();
}


void Engine::Quit() {
	m_IsRunning = false;
}



Engine::~Engine()
{
	delete s_Instance;
	delete m_Window;
	delete m_Renderer;
	//delete game_screen_manager;
	delete g_music;
	delete m_LevelMap;
}




void Engine::InitMap(string ID, int level) {
	if (!MapParser::GetInstance()->Load(level))
	{
	cout << "Failed to load map" << endl;
	}

m_LevelMap = MapParser::GetInstance()->GetMap(ID);
}
void Engine::UpdateMap() {
	m_LevelMap->Update();
}
void Engine::RenderMap() {
	m_LevelMap->Render();
}


void Engine::CleanMap() {
	m_LevelMap->Clean();
}


void Engine::InitMap2(string ID, int level) {
	if (!MapParser::GetInstance()->Load(level))
	{
	cout << "Failed to load map" << endl;
	}

m_LevelMap2 = MapParser::GetInstance()->GetMap(ID);
}
void Engine::UpdateMap2() {
	m_LevelMap2->Update();
}
void Engine::RenderMap2() {
	m_LevelMap2->Render();
}


void Engine::CleanMap2() {
	m_LevelMap2->Clean();
}

