#pragma once
#define MUNCHIECOUNT 435
#define CHERRYCOUNT 10
#define GHOSTCOUNT 3
#define DEADGHOST 3
#define BLOCKS 281
#include <ctime>//time for the srand
#include <cstdlib> 
#include <array>
#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

// If Windows and not in Debug, this will run without a console window
// You can use this to output information when debugging using cout or cerr
#ifdef WIN32 

#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif
#endif



// Just need to include main header file
#include "S2D/S2D.h"

// Reduces the amount of typing by including all classes in S2D namespace
using namespace S2D;

// Declares the Pacman class which inherits from the Game class.
// This allows us to overload the Game class methods to help us
// load content, draw and update our game.

struct Player {
	bool _isDead;
	float speedMultiplier;
	int currentFrameTime;
	int Direction;
	int frame;
	Rect* sourceRect;
	Texture2D* texture;
	Vector2* position;
};

struct Enemy
{
	int _frameCount;
	Rect* Rect;
	Texture2D* Texture;
	Texture2D* InvertedTexture;
	Vector2* Position;
	int Frame;
	int CurrentFrameTime;
};

struct CherryMunchie
{
	int _frameCount;
	Rect* Rect;
	Texture2D* Texture;
	Texture2D* InvertedTexture;
	Vector2* Position;
	int Frame;
	int CurrentFrameTime;
};

struct MovingEnemy
{
	Vector2* position;
	Texture2D* texture;
	Rect* sourceRect;
	int direction;
	float speed;
};

struct DeadGhost
{
	int _frameCount;
	int currentFrameTime;
	Vector2* position;
	Texture2D* texture;
	Texture2D* InvertedTexture;
	Rect* sourceRect;
	int direction;
	float speed;
	int Frame;
};

struct Screen
{
	Texture2D* _menuBackground;
	Rect* _menuRectangle;
	Vector2* _menuStringPosition;
};

struct Square
{
	Texture2D* block;
	Rect* rect;
	Vector2* Position;
};

struct MapColliders
{
	Rect* sourceRect;
	Vector2* position;
};

class Pacman : public Game
{
private:

	//Input Methods
	void Input(int elapsedTime, Input::KeyboardState* state, Input::MouseState* mouseState);

	//Check methods
	void CheckPaused(Input::KeyboardState* state, Input::Keys pauseKey);
	void CheckInGame(Input::KeyboardState* state, Input::Keys StartKey);
	void CheckGameOver(Input::KeyboardState* state, Input::Keys StartKey);
	void CheckViewportCollision();
	void CheckGhostCollisions();
	void CheckDeadGhostCollisions();
	void CheckMunchieCollisions();
	void CheckCherryCollisions();
	void CheckMapCollisions();
	void CheckMapGhostCollisions(MovingEnemy* ghost);
	void CheckMapDeadGhostCollisions(DeadGhost* ghost);
	void Dead();
	void Timer();


	//Update Methods
	void UpdatePacman(int elapsedTime);
	void UpdateMuchies(Enemy* munchie, int elapsedTime);
	void UpdateCherry(int elapsedTime);
	void UpdateDeadGhost(int elapsedTime);
	void UpdateGhost(MovingEnemy* ghost, int elapsedTime, float& pacmanX, float& pacmanY, int& pacmanDir);
	void UpdateDeadGhost(DeadGhost* ghost, int elapsedTime, float& pacmanX, float& pacmanY, int& pacmanDir);



	// Data to represent Pacman
	//Vector2* _pacmanPosition;
	//Rect* _pacmanSourceRect;
	//Texture2D* _pacmanTexture;
	//Texture2D* _pacmanOpenMouthTexture;
	//int _pacmanDirection;
	//int _pacmanFrame; 
	//int _pacmanCurrentFrameTime;


	//Enemy* _munchie;
	int fileHighScore;
	int highscore = 0;
	int score = 0;
	int ScoreChecker = 0;

	ifstream infile;
	ofstream outfile;


	Player* _pacman;
	Enemy* _munchie[MUNCHIECOUNT];
	MovingEnemy* _ghosts[GHOSTCOUNT];
	DeadGhost* _deadGhost[GHOSTCOUNT];
	CherryMunchie* _cherryMunchie[CHERRYCOUNT];
	Screen* _menu;
	Screen* _pause;
	Screen* _gameOverScreen;
	Screen* _Map;
	SoundEffect* _eatGhost;
	SoundEffect* _beginning;
	SoundEffect* _chomp;
	SoundEffect* _death;
	SoundEffect* _eatfruit;
	SoundEffect* _inGame;

	Square* _square[BLOCKS];
	int _colliders[768] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,3,3,3,3,3,3,3,3,3,3,3,3,3,2,1,1,2,3,3,3,3,3,3,3,3,3,3,3,3,3,1,
		1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,
		1,3,3,1,1,1,3,3,3,1,1,1,1,3,3,1,1,3,3,1,1,1,1,3,3,3,1,1,1,3,3,1,
		1,3,3,3,3,3,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,3,3,3,3,3,1,
		1,3,3,1,1,1,3,3,3,3,3,3,1,1,1,1,1,1,1,1,3,3,1,3,3,3,1,1,1,3,3,1,
		1,3,3,3,3,3,3,3,3,1,3,3,3,3,3,1,3,3,3,3,3,3,1,3,3,3,3,3,3,3,3,1,
		1,1,1,1,1,1,3,2,3,1,1,1,1,3,3,1,3,3,3,3,3,3,1,3,2,3,1,1,1,1,1,1,
		0,0,0,0,0,1,3,3,3,1,3,3,3,3,3,3,3,3,3,1,1,1,1,3,3,3,1,0,0,0,0,0,
		0,0,0,0,0,1,3,3,3,1,3,3,3,3,3,3,3,3,3,3,3,3,1,3,3,3,1,0,0,0,0,0,
		1,1,1,1,1,1,3,3,3,1,3,3,1,0,0,0,0,0,0,1,3,3,1,3,3,3,1,1,1,1,1,1,
		3,3,3,3,3,3,3,3,3,3,3,3,1,0,0,0,0,0,0,1,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,3,3,3,3,1,3,3,1,1,1,1,1,1,1,1,3,3,1,3,3,3,3,3,3,3,3,3,
		1,1,1,1,1,1,3,3,3,1,3,3,3,3,3,3,3,3,3,3,3,3,1,3,3,3,1,1,1,1,1,1,
		0,0,0,0,0,1,3,3,2,1,3,3,3,3,3,3,3,3,3,3,3,3,1,2,3,3,1,0,0,0,0,0,
		1,1,1,1,1,1,3,3,3,3,3,3,1,1,1,1,1,1,1,1,3,3,3,3,3,3,1,1,1,1,1,1,
		1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,
		1,3,3,1,1,1,3,3,3,1,1,1,1,3,3,1,3,3,3,1,1,1,1,3,3,3,1,1,1,3,3,1,
		1,3,3,3,3,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,3,3,3,3,1,
		1,1,1,3,3,1,3,3,3,1,3,3,1,1,1,1,1,1,1,1,3,3,1,3,3,3,1,3,3,1,1,1,
		1,2,3,3,3,3,3,3,3,1,3,3,3,3,3,1,3,3,3,3,3,3,1,3,3,3,3,3,3,3,2,1,
		1,3,3,1,1,1,1,1,1,1,1,1,1,3,3,1,3,3,3,1,1,1,1,1,1,1,1,1,1,3,3,1,
		1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
	};




	// Data to represent Munchie
	//int _frameCount;
	//Rect* _munchieRect;
	//Texture2D* _munchieBlueTexture;
	//Texture2D* _munchieInvertedTexture;
	//Vector2* _munchiePosition;
	//int _munchieFrame; 
	//int _munchieCurrentFrameTime;

	//int _cherryframeCount;
	//Rect* _cherryRect;
	//Texture2D* _cherryTexture;
	//Texture2D* _cherryInvertedTexture;
	//Vector2* _cherryPosition;
	//int _cherryFrame; 
	//int _cherryCurrentFrameTime;

	// Position for String
	Vector2* _stringPosition;

	//Constant data for Game Variables
	const float _cPacmanSpeed;
	const int _cPacmanFrameTime;
	const int _cMunchieFrameTime;
	const int _cCherryFrameTime;

	// Data for Menu

	bool _paused;

	bool  _pKeyDown;


	bool _gameOver;

	bool _restartKey;


	bool _isInGame;

	bool _SkeyDown;

	bool _chaseGhost;

	bool _ghostIsEaten;


public:


	/// <summary> Constructs the Pacman class. </summary>
	Pacman(int argc, char* argv[]);

	/// <summary> Destroys any data associated with Pacman class. </summary>
	virtual ~Pacman();

	/// <summary> All content should be loaded in this method. </summary>
	void virtual LoadContent();

	/// <summary> Called every frame - update game logic here. </summary>
	void virtual Update(int elapsedTime);

	/// <summary> Called every frame - draw game here. </summary>
	void virtual Draw(int elapsedTime);
};