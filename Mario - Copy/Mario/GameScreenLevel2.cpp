#include "GameScreenLevel2.h"
#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include <iostream>
#include <ctime>
#include <cstdlib>


GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer) : GameScreen(renderer)
{
	Collisions::Instance()->m_level = 2;
	srand(time(0));
	m_Lives = 3;
	m_Time = 200;
	m_CanCollide = true;
	frameCount = 0;
	Engine::GetInstance()->InitMap2("Level2",1);

	TextureAnim::GetInstance()->LoadTexture("smallPlayerIdle", "Images/MarioSpritesheet/SmallMario.png");
	TextureAnim::GetInstance()->LoadTexture("playerIdle", "Images/MarioSpritesheet/BigMarioIdle.png");
	TextureAnim::GetInstance()->LoadTexture("playerRun", "Images/MarioSpritesheet/BigMarioRun(2).png");
	TextureAnim::GetInstance()->LoadTexture("playerJump", "Images/MarioSpritesheet/BigMarioJump.png");


	TextureAnim::GetInstance()->LoadTexture("Bg", "Images/back.png");
	Mario = new CharacterMario(new Properties("playerIdle", 100, 0, 30, 69));
	Mario->SetCanMove(true);

	TextureAnim::GetInstance()->LoadTexture("EnemyMoving", "Images/MarioSpritesheet/KoopaBigger.png");
	Camera::GetInstance()->SetTarget(Mario->GetOrigin());


	ArrayTxt();

}

void GameScreenLevel2::ArrayTxt() {
	m_LevelUI = new TextManager(m_renderer, textSurface, texture, 20, "Freedom-10eM.ttf", font);
	m_LevelIntUI = new TextManager(m_renderer, textSurface, texture, 15, "SuperMario256.ttf", font);

	m_UInamesArr[0] = "Score";
	m_UInamesArr[1] = "Coins";
	m_UInamesArr[2] = "Level";
	m_UInamesArr[3] = "Time";
	m_UInamesArr[4] = "Lives";

	m_UIints[0] = "7";
	m_UIints[1] = "2";
	m_UIints[2] = "1";
	m_UIints[3] = "5";
	m_UIints[4] = "3";
	string s;
	string coin;
	for (int i = 0; i < 50; i++)
	{
		s = to_string(i);
		coin = "Coins" + s;
		TextureAnim::GetInstance()->LoadTexture(coin, "Images/coin.png");
	}
	for (int i = 0; i < 50; i++)
	{
		Vector2D randPos;
		randPos.X = (rand() % 4000) + 2000;
		randPos.Y = (rand() % 300) + 300;
		s = to_string(i);
		coin = "Coins" + s;

		coins = new Coins(new Properties(coin, randPos.X, randPos.Y, 16, 22));
		m_CoinsObj.push_back(coins);

	}
	for (int i = 0; i < 10; i++)
	{
		Vector2D randPos;
		randPos.X = (rand() % 4000) + 2000;
		randPos.Y = (rand() % 300) + 300;
		CreateKoopa(randPos.X, 500);
	}

	for (int i = 0; i < 5; i++)
	{
		m_UIPos[i] = Vector2D((i * 150) + 200);
	}
}

void GameScreenLevel2::Clean() {

}


void GameScreenLevel2::Render() {

	TextureAnim::GetInstance()->Draw("Bg", 0, 0, 2100, SCREEN_HEIGHT, 1, 1, 0.5f);
	Engine::GetInstance()->RenderMap2();
	Mario->Render();
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
	}
	//Luigi->Render();
	m_pow_block->Render();

	for (int i = 0; i < m_CoinsObj.size(); i++)
	{
		m_CoinsObj[i]->Render();
	}

	for (int i = 0; i < 5; i++)
	{
		textRect.x = m_UIPos[i].X;
		textRect.y = m_UIPos[i].Y;
		textRect.h = 40;
		textRect.w = 90;

		m_LevelUI->DrawText(m_UIPos[i].X, m_UIPos[i].Y, textRect.w, textRect.h, m_UInamesArr[i], COLOUR.BLUE);
		m_LevelUI->Renderer();
		m_LevelIntUI->DrawText(textRect.x + 15, textRect.y + 20, textRect.w, textRect.h, m_UIints[i], COLOUR.WHITE);
		m_LevelIntUI->Renderer();

	}

}




void GameScreenLevel2::Update(float deltaTime) {




	//while (!m_levelComplete)
	//{
	Mario->Update(deltaTime);
	//koopa->Update(deltaTime);

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Update(deltaTime);
	}
	for (int i = 0; i < m_enemies.size(); i++)
	{

		if (Collisions::Instance()->CheckCollision(Mario->GetCollider()->Get(), m_enemies[i]->GetCollider()->Get()) && m_CanCollide) //(Collisions::Instance()->Circle(Mario, koopa) && m_CanCollide)
		{
			m_CanCollide = false;
			m_Lives--;
		}
		else if (!Collisions::Instance()->CheckCollision(Mario->GetCollider()->Get(), m_enemies[i]->GetCollider()->Get()))//(!Collisions::Instance()->Circle(Mario, koopa))
		{
			m_CanCollide = true;

		}
		else if (Collisions::Instance()->CheckCollision(Mario->GetCollider()->Get(), m_enemies[i]->GetDeadCollider()->Get()) && m_CanCollide == true)
		{
			cout << "HOOOZAHH" << endl;
			m_enemies.erase(m_enemies.begin() + i);
			m_Score += 100;
			Mario->SetPosition(new Transform(Mario->GetPosition()->X, Mario->GetPosition()->Y + 25));
		}
	}
	for (int i = 0; i < m_CoinsObj.size(); i++)
	{
		m_CoinsObj[i]->Update(deltaTime);
		if (Collisions::Instance()->Circle(Mario, m_CoinsObj[i]))
		{
			m_Score += 10;
			m_Coins++;
			m_CoinsObj.erase(m_CoinsObj.begin() + i);
			//string s = to_string(i);
			//m_CoinsObj[i]->Clean(s);
			cout << "isssaaaa goal" << endl;
		}
	}







	frameCount++;
	if (frameCount == 60)
	{
		m_Time -= 1;
		frameCount = 0;
	}

	string s = to_string(m_Score);
	string c = to_string(m_Coins);
	string t = to_string(m_Time);
	string l = to_string(m_Lives);

	m_UIints[0] = s;
	m_UIints[1] = c;
	m_UIints[3] = t;
	m_UIints[4] = l;
	Camera::GetInstance()->Update(deltaTime);
	Engine::GetInstance()->UpdateMap2();
	//if (m_Time <= 0 && !m_levelComplete)
	//{
	//	m_LevelFailed = true;
	//}
	//if (m_Lives <= 0 && !m_levelComplete) {
	//	m_LevelFailed = true;
	//}
	//if (Mario->GetPosition()->X >= 6918 && m_Time > 0)
	//{
	//	m_levelComplete = true;
	//	Mario->SetCanMove(false);
	//}
	//if (m_LevelFailed)
	//{
	//	break;
	//}

//}
//if (m_LevelFailed)
//{
//	gameScreen->ChangeScreens(SCREEN_INTRO);
//	m_Score = 0;
//}
	//if (m_levelComplete)
	//{
	//	m_Score = m_Score + (m_Time * 50);
	//	m_Time = 0;
	//}


}


void GameScreenLevel2::UpdateEnemies(float deltaTime) {

}

void GameScreenLevel2::CreateKoopa(int x, int y) {
	koopa = new CharacterKoopa(new Properties("EnemyMoving", x, y, 60, 60));
	m_enemies.push_back(koopa);
}


void GameScreenLevel2::UpdatePowBlock() {
	/*if (Collisions::Instance()->Box(m_pow_block->GetCollisionBox(), Mario->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable()) {
			if (Mario->IsJumping())
			{
				DoScreenshake();
				m_pow_block->TakeHit();
				Mario->CancelJump();
			}


		}
		cout << "PPPPPPPPPPPOOOOOOOOOOOOOOWWWWWWWWWWWW" << endl;
	}*/
}



bool GameScreenLevel2::SetUpLevel() {



	m_pow_block = new POWblock(m_renderer, m_level_map);
	m_screenShake = false;
	m_background_yPos = 0.0f;
	m_background_texture = new Texture2D(m_renderer);


	return true;
}

void GameScreenLevel2::DoScreenshake() {
	m_screenShake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}
}


void GameScreenLevel2::SetLevelMap() {
	int map[MAP_HEIGHT][MAP_WIDTH] =
	{ { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
	  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	  { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
	  { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
	  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	  { 0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0 },
	  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
	  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	  { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };



	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}
	//set the new one
		//m_level_map = new LevelMap(map);


}



GameScreenLevel2::~GameScreenLevel2() {
	m_background_texture = nullptr;
	delete Mario;
	Mario = nullptr;
	delete m_LevelUI;
	delete m_LevelIntUI;
	delete font;
	delete textSurface;
	delete texture;
	delete	Mario;
	delete koopa;
	delete m_level_map;
	delete m_pow_block;
	delete m_LevelMap;
	//delete Luigi;
	//Luigi = nullptr;
	delete m_pow_block;
	m_pow_block = nullptr;
	m_enemies.clear();
}