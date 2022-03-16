#include "Pacman.h"
//#define MUNCHIECOUNT 50
#include <sstream>
#include <array>
#include<conio.h>



Pacman::Pacman(int argc, char* argv[]) : Game(argc, argv), _cPacmanSpeed(0.1f), _cPacmanFrameTime(250), _cMunchieFrameTime(500), _cCherryFrameTime(500)
{

	srand(time(0));
	infile.open("Scores.txt");
	if (!infile.is_open()) {
		cout << "File failed to Open" << endl;
	}	

	

	_pacman = new Player();
	_pacman->_isDead = false;
	_pacman->currentFrameTime = 0;
	_pacman->Direction = 0;
	_pacman->frame = 0;

	_menu = new Screen();
	_menu->_menuBackground;
	_menu->_menuRectangle;
	_menu->_menuStringPosition;

	_gameOverScreen = new Screen();
	_gameOverScreen->_menuBackground;
	_gameOverScreen->_menuRectangle;
	_gameOverScreen->_menuStringPosition;

	_pause = new Screen();
	_pause->_menuBackground;
	_pause->_menuRectangle;
	_pause->_menuStringPosition;



	_chomp = new SoundEffect();
	_beginning = new SoundEffect();
	_death = new SoundEffect();
	_eatfruit = new SoundEffect();
	_eatGhost = new SoundEffect();
	_inGame = new SoundEffect();

	for (int i = 0; i < BLOCKS; i++)
	{
		_square[i] = new Square();
	}

	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		_munchie[i] = new Enemy();
		//_munchie[i]->CurrentFrameTime = 0;
		_munchie[i]->_frameCount = rand() % 1;
		_munchie[i]->CurrentFrameTime = 0;
		_munchie[i]->Frame = rand() % 500 * 50;

	}
	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		_ghosts[i] = new MovingEnemy();
		_ghosts[i]->direction = 0;
		_ghosts[i]->speed = 0.2f;
	}
	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		_deadGhost[i] = new DeadGhost();
		_deadGhost[i]->direction = _ghosts[i]->direction;
		_deadGhost[i]->speed = 0.2f;
		_deadGhost[i]->currentFrameTime = 0;
		_deadGhost[i]->direction = _ghosts[i]->direction = 0;
		_deadGhost[i]->currentFrameTime = 0;
		_deadGhost[i]->_frameCount = rand() % 1;
	}	


	for (int i = 0; i < CHERRYCOUNT; i++)
	{
		_cherryMunchie[i] = new CherryMunchie();
		_cherryMunchie[i]->_frameCount = 0;
		_cherryMunchie[i]->CurrentFrameTime = 0;
	}

	while (infile >> fileHighScore)
	{
		highscore = fileHighScore;
	}
	infile.close();

	_isInGame = false;
	Audio::Play(_inGame);
	_SkeyDown = false;

	_paused = false;

	_pKeyDown = false;

	_gameOver = false;

	_restartKey = false;

	_chaseGhost = false;

	_ghostIsEaten = false;

	//Initialise important Game aspects
	Audio::Initialise();
	if (!Audio::IsInitialised()) {
		cout << "Audio is not Initialised" << endl;
	}
	Graphics::Initialise(argc, argv, this, 1024, 768, false, 25, 25, "Pacman", 60);
	Input::Initialise();

	// Start the Game Loop - This calls Update and Draw in game loop
	Graphics::StartGameLoop();

}

Pacman::~Pacman()
{
	//delete _pacmanTexture;
	//delete _pacmanOpenMouthTexture;
	//delete _pacmanSourceRect;
	delete _pacman->texture;
	delete _pacman->sourceRect;
	delete _pacman->position;
	delete _pacman;

	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		delete _ghosts[i]->position;
		delete _ghosts[i]->sourceRect;
		delete _ghosts[i]->texture;
		delete _ghosts[i];
		delete _deadGhost[i]->InvertedTexture;
		delete _deadGhost[i]->texture;
		delete _deadGhost[i]->sourceRect;
		delete _deadGhost[i]->position;
		delete _deadGhost[i];
	}
	delete[] _ghosts;


	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		delete _munchie[i]->Position;
		delete _munchie[i]->Texture;
		delete _munchie[i]->Rect;
		delete _munchie[i];
		delete _munchie[i]->InvertedTexture;
		delete _munchie[i]->Position;
	}
	delete[] _munchie;

	delete _chomp;
	delete _beginning;
	delete _death;
	delete _eatfruit;
	delete _eatGhost;
	delete _inGame;

	delete _menu->_menuBackground;
	delete _menu->_menuRectangle;
	delete _pause->_menuBackground;
	delete _pause->_menuRectangle;
	delete _gameOverScreen->_menuBackground;
	delete _gameOverScreen->_menuRectangle;

	for (int i = 0; i < CHERRYCOUNT; i++)
	{
		delete _cherryMunchie[i]->Texture;
		delete _cherryMunchie[i]->InvertedTexture;
		delete _cherryMunchie[i]->Rect;
	}


	for (int i = 0; i < BLOCKS; i++)
	{
		delete _square[i]->block;
		delete _square[i]->rect;
		delete _square[i]->Position;
	}

}

void Pacman::LoadContent()
{
	//srand(time(0));
		//main menu 
	_menu->_menuBackground = new Texture2D();
	//_menu->_menuBackground = new Texture2D();
	_menu->_menuBackground->Load("Textures/PacmanMenu.jpg", false);
	_menu->_menuRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	_menu->_menuStringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f, Graphics::GetViewportHeight() / 2.0f);

	//pause menu 
	_pause->_menuBackground = new Texture2D();
	_pause->_menuBackground->Load("Textures/Transparency.png", false);
	_pause->_menuRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(),
		Graphics::GetViewportHeight());
	_pause->_menuStringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f,
		Graphics::GetViewportHeight() / 2.0f);

	//GameOver Menu
	_gameOverScreen->_menuBackground = new Texture2D();
	_gameOverScreen->_menuBackground->Load("Textures/pac-man-game-over.jpg", false);
	_gameOverScreen->_menuRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(),
		Graphics::GetViewportHeight());
	_gameOverScreen->_menuStringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f,
		Graphics::GetViewportHeight() / 2.0f);

	//Load Sound
	_chomp->Load("Sounds/pacman_chomp.wav");
	if (!_chomp->IsLoaded()) {
		cout << "_chomp member sound effect has not loaded" << endl;
	}	
	_beginning->Load("Sounds/pacman_beginning.wav");
	if (!_beginning->IsLoaded()) {
		cout << "_beginning member sound effect has not loaded" << endl;
	}	
	_beginning->SetLooping(true);
	_death->Load("Sounds/pacman_death.wav");
	if (!_death->IsLoaded()) {
		cout << "_death member sound effect has not loaded" << endl;
	}	
	_eatfruit->Load("Sounds/pacman_eatfruit.wav");
	if (!_eatfruit->IsLoaded()) {
		cout << "_eatfruit member sound effect has not loaded" << endl;
	}	
	_eatGhost->Load("Sounds/pacman_eatghost.wav");
	if (!_eatGhost->IsLoaded()) {
		cout << "_eatGhost member sound effect has not loaded" << endl;
	}
	_inGame->Load("Sounds/pacman_intro.wav");
	if (!_eatGhost->IsLoaded()) {
		cout << "_inGame member sound effect has not loaded" << endl;
	}


	//Load Map

	// Load Pacman
	_pacman->texture = new Texture2D();
	_pacman->texture->Load("Textures/Pacman.tga", false);
	_pacman->position = new Vector2(30.0f, 30.0f);
	_pacman->sourceRect = new Rect(0.0f, 0.0f, 32, 32);

	for (int i = 0; i < BLOCKS; i++)
	{
		_square[i]->block = new Texture2D();
		_square[i]->block->Load("Textures/red square.png", false);
		_square[i]->rect = new Rect(0.0f, 0.0f, 32, 32);

	}


	// Load Munchie
	//_munchie[i]->Texture = new Texture2D();

	Texture2D* munchieTex = new Texture2D();
	munchieTex->Load("Textures/Munchies.png", true);
	Texture2D* invertedMuchieTex = new Texture2D();
	invertedMuchieTex->Load("Textures/Munchies.png", true);
	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		_munchie[i]->Texture = munchieTex;
		_munchie[i]->InvertedTexture = invertedMuchieTex;
		_munchie[i]->Rect = new Rect(0.0f, 0.0f, 32, 32);
		//_munchie[i]->Position = new Vector2((rand() % Graphics::GetViewportWidth()), (rand() % Graphics::GetViewportHeight()));
		//CheckMunchieOnMunchieCollisions();

	}



	// Load cherry
	for (int i = 0; i < CHERRYCOUNT; i++)
	{
		_cherryMunchie[i]->Texture = new Texture2D();
		_cherryMunchie[i]->Texture->Load("Textures/CherryTexture.png", true);
		_cherryMunchie[i]->InvertedTexture = new Texture2D();
		_cherryMunchie[i]->InvertedTexture->Load("Textures/CherryTexture.png", true);
		_cherryMunchie[i]->Rect = new Rect(0.0f, 0.0f, 32, 32);
		//_cherryMunchie->Position = new Vector2((rand() % Graphics::GetViewportWidth()), (rand() % Graphics::GetViewportHeight()));
	}



	//Load Ghosts
	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		_ghosts[i]->texture = new Texture2D();
		_ghosts[i]->texture->Load("Textures/All Ghost.png", false);
		_ghosts[i]->position = new Vector2(514, 364);
		_ghosts[i]->sourceRect = new Rect(i * 32, 0, 32, 32);
		_ghosts[i]->direction = (rand() % 4) + 1;
	}

	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		_deadGhost[i]->texture = new Texture2D();
		_deadGhost[i]->texture->Load("Textures/NewDeadGhost.png", false);
		_deadGhost[i]->InvertedTexture = new Texture2D();
		_deadGhost[i]->InvertedTexture->Load("Textures/NewDeadGhost.png", true);
		_deadGhost[i]->position = new Vector2(_ghosts[i]->position->X, _ghosts[i]->position->Y);
		_deadGhost[i]->sourceRect = new Rect(0, 0, 32, 32);
		_deadGhost[i]->direction = (rand() % 4) + 1;
	}


	// Set string position
	_stringPosition = new Vector2(10.0f, 25.0f);

	for (int i = 0, j = 0, k = 0, l = 0; i < 768; i++)
	{
		if (_colliders[i] == 3) {
			_munchie[l]->Position = new Vector2((i % 32) * 32, (i / 32) * 32);
			l++;
		}
		if (_colliders[i] == 1) {
			_square[j]->Position = new Vector2((i % 32) * 32, (i / 32) * 32);
			j++;
		}
		if (_colliders[i] == 2)
		{
			_cherryMunchie[k]->Position = new Vector2((i % 32) * 32, (i / 32) * 32);
			k++;
		}
	}

	Audio::Play(_inGame);
	
}

void Pacman::Update(int elapsedTime)
{
	// Gets the current state of the keyboard
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();
	Input::MouseState* mouseState = Input::Mouse::GetState();
	if (!_isInGame) {
		
		CheckInGame(keyboardState, Input::Keys::SPACE);

	}

	if (_isInGame)
	{
		
		if (!_pacman->_isDead) {

			CheckPaused(keyboardState, Input::Keys::P);

			if (!_paused)
			{
				Input(elapsedTime, keyboardState, mouseState);
				UpdatePacman(elapsedTime);
				UpdateCherry(elapsedTime);
				CheckViewportCollision();
				

				
				CheckMunchieCollisions();
				CheckMapCollisions();
				CheckCherryCollisions();
				
				if (score > highscore) {
					outfile.open("Scores.txt");
					if (!outfile.is_open()) {
						cout << "File failed to Open" << endl;
					}
					highscore = score;
					fileHighScore = highscore;
					outfile << fileHighScore << endl;
					outfile.close();
				}

				//
				if (!_chaseGhost)
				{
					for (int i = 0; i < GHOSTCOUNT; i++)
					{
						UpdateGhost(_ghosts[i], elapsedTime, _pacman->position->X, _pacman->position->Y, _pacman->Direction);
						CheckGhostCollisions();
						CheckMapGhostCollisions(_ghosts[i]);
					}
				}
				else
				{
					
					for (int i = 0; i < GHOSTCOUNT; i++)
					{
						UpdateDeadGhost(_deadGhost[i], elapsedTime, _pacman->position->X, _pacman->position->Y, _pacman->Direction);
						UpdateDeadGhost(elapsedTime);
						CheckMapDeadGhostCollisions(_deadGhost[i]);
						if (!_ghostIsEaten)
						{
							CheckDeadGhostCollisions();
							
							Timer();
							
						}
					}
				}

				

				for (int i = 0; i < MUNCHIECOUNT; i++)
				{
					UpdateMuchies(_munchie[i], elapsedTime);
				}

				//if (_pacmanPosition->X > Graphics::GetViewportWidth())
				//{
				//	// Pacman hit right wall - reset his position
				//	_pacmanPosition->X = -_pacmanSourceRect->Width;
				//}
				// if (_pacmanPosition->X < Graphics::GetViewportWidth())
				//{
				//	// Pacman hit right wall - reset his position
				//	_pacmanPosition->X = -_pacmanSourceRect->Width;
				//}
			}
			else {
				
			}
		}
		else
		{

			CheckGameOver(keyboardState, Input::Keys::R);
		}


	}


}

void Pacman::Draw(int elapsedTime)
{
	// Allows us to easily create a string
	std::stringstream stream;
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();
	SpriteBatch::BeginDraw();

	if (!_isInGame)
	{
		std::stringstream menuStream;
		//menuStream << "PLAY!";
		SpriteBatch::Draw(_menu->_menuBackground, _menu->_menuRectangle, nullptr);
		SpriteBatch::DrawString(menuStream.str().c_str(), _menu->_menuStringPosition, Color::Red);
	}
	else {

		for (int i = 0; i < BLOCKS; i++)
		{
			SpriteBatch::Draw(_square[i]->block, _square[i]->Position, _square[i]->rect);
		}
		//stream << "Pacman X: " << _pacman->position->X << " Y: " << _pacman->position->Y;
		stream << "\t\t\tHigh Score " << highscore;
		stream << "\t\t\tScore " << score;


		// Starts Drawing
		if (!_pacman->_isDead)
		{
			SpriteBatch::Draw(_pacman->texture, _pacman->position, _pacman->sourceRect); // Draws Pacman

		}
		else if (_isInGame && _pacman->_isDead) {
			std::stringstream menuStream;
			//menuStream << "GAME OVER! PRESS R TO RESTART";
			SpriteBatch::Draw(_gameOverScreen->_menuBackground, _gameOverScreen->_menuRectangle, nullptr);
			SpriteBatch::DrawString(menuStream.str().c_str(), _gameOverScreen->_menuStringPosition, Color::Red);
		}

		if (_chaseGhost == false)
		{
			for (int i = 0; i < GHOSTCOUNT; i++)
			{
				SpriteBatch::Draw(_ghosts[i]->texture, _ghosts[i]->position, _ghosts[i]->sourceRect);
			}
		}
		else if (_chaseGhost)
		{
			for (int i = 0; i < GHOSTCOUNT; i++)
			{
				if (_deadGhost[i]->_frameCount == 0)
				{
					SpriteBatch::Draw(_deadGhost[i]->texture, _deadGhost[i]->position, _deadGhost[i]->sourceRect);
					//SpriteBatch::Draw(_munchieInvertedTexture, _munchieRect, nullptr, new Vector2(350.0f, 350.0f), 1.0f, 0.0f, Color::White, SpriteEffect::NONE);

				}
				else
				{
					SpriteBatch::Draw(_deadGhost[i]->InvertedTexture, _deadGhost[i]->position, _deadGhost[i]->sourceRect);

					if (_deadGhost[i]->_frameCount >= 60)
						_deadGhost[i]->_frameCount = 0;


				}
			}
		}



		for (int i = 0; i < MUNCHIECOUNT; i++)
		{


			if (_munchie[i]->_frameCount == 0)
			{
				// Draws blue Munchie
				//SpriteBatch::Draw(_munchieBlueTexture, new Vector2(350.0f, 350.0f), _munchieRect);
				SpriteBatch::Draw(_munchie[i]->Texture, _munchie[i]->Position, _munchie[i]->Rect);
				//SpriteBatch::Draw(_munchieInvertedTexture, _munchieRect, nullptr, new Vector2(350.0f, 350.0f), 1.0f, 0.0f, Color::White, SpriteEffect::NONE);

			}
			else
			{
				// Draw Inverted Munchie
				SpriteBatch::Draw(_munchie[i]->InvertedTexture, _munchie[i]->Position, _munchie[i]->Rect);
				//SpriteBatch::Draw(_munchieBlueTexture, _munchieRect, nullptr, new Vector2(350.0f, 350.0f), 1.0f, 0.0f, Color::White, SpriteEffect::NONE);


				if (_munchie[i]->_frameCount >= 60)
					_munchie[i]->_frameCount = 0;


			}
		}
		for (int i = 0; i < CHERRYCOUNT; i++)
		{
			if (_cherryMunchie[i]->_frameCount == 0)
			{

				SpriteBatch::Draw(_cherryMunchie[i]->InvertedTexture, _cherryMunchie[i]->Position, _cherryMunchie[i]->Rect);
			}
			else
			{

				SpriteBatch::Draw(_cherryMunchie[i]->Texture, _cherryMunchie[i]->Position, _cherryMunchie[i]->Rect);



				if (_cherryMunchie[i]->_frameCount >= 60)
					_cherryMunchie[i]->_frameCount = 0;

			}
		}

		if (_paused)
		{
			std::stringstream menuStream;
			menuStream << "PAUSED!";
			SpriteBatch::Draw(_pause->_menuBackground, _pause->_menuRectangle, nullptr);
			SpriteBatch::DrawString(menuStream.str().c_str(), _pause->_menuStringPosition, Color::Red);
		}
	}SpriteBatch::DrawString(stream.str().c_str(), _stringPosition, Color::Green);

	// Draws String

	SpriteBatch::EndDraw(); // Ends Drawing
}



void Pacman::Dead() {

	_pacman->position = new Vector2(30.0f, 30.0f);

	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		_ghosts[i]->position = new Vector2((rand() % 30) + (Graphics::GetViewportWidth() / 2), (rand() % 30) + (Graphics::GetViewportHeight()/2 ));
	}

	for (int i = 0, j = 0, k = 0, l = 0; i < 768; i++)
	{
		if (_colliders[i] == 3) {
			_munchie[l]->Position = new Vector2((i % 32) * 32, (i / 32) * 32);
			l++;
		}
		if (_colliders[i] == 2) {
			_cherryMunchie[k]->Position = new Vector2((i % 32) * 32, (i / 32) * 32);
			k++;
		}
	}
	Audio::Play(_beginning);
	
	score = 0;

}

void Pacman::Timer() {

	if (ScoreChecker == 400) {
		_chaseGhost = false;
	}
	//_chaseGhost = false;
}

	






void Pacman::Input(int elapsedTime, Input::KeyboardState* state, Input::MouseState* mouseState)
{
	if (state->IsKeyDown(Input::Keys::D)) {
		_pacman->position->X += _cPacmanSpeed * elapsedTime * _pacman->speedMultiplier;//Moves Pacman across X axis to the right
		_pacman->Direction = 4;
	}
	else if (state->IsKeyDown(Input::Keys::A)) {
		_pacman->position->X += -_cPacmanSpeed * elapsedTime * _pacman->speedMultiplier; //Moves Pacman across X axis to the left
		_pacman->Direction = 2;
	}
	else if (state->IsKeyDown(Input::Keys::W))
	{
		_pacman->position->Y -= _cPacmanSpeed * elapsedTime * _pacman->speedMultiplier; //Moves Pacman across Y axis Upwards
		_pacman->Direction = 3;
	}
	else if (state->IsKeyDown(Input::Keys::S))
	{
		_pacman->position->Y += _cPacmanSpeed * elapsedTime * _pacman->speedMultiplier; //Moves Pacman across Y axis Downwards
		_pacman->Direction = 1;
	}
	if (state->IsKeyDown(Input::Keys::LEFTSHIFT)) {
		_pacman->speedMultiplier = 2.0f;
	}
	else
	{
		_pacman->speedMultiplier = 1.0f;
	}


	if (mouseState->LeftButton == Input::ButtonState::PRESSED) {
		//_cherryMunchie->Position->X = mouseState->X;
		//_cherryMunchie->Position->Y = mouseState->Y;
	}



}

void Pacman::CheckGhostCollisions() {
	int i = 0;
	int bottom1 = _pacman->position->Y + (_pacman->sourceRect->Height - 4);
	int bottom2 = 0;
	int left1 = _pacman->position->X;
	int left2 = 0;
	int right1 = _pacman->position->X + (_pacman->sourceRect->Width - 4);
	int right2 = 0;
	int top1 = _pacman->position->Y;
	int top2 = 0;

	for (i = 0; i < GHOSTCOUNT; i++)
	{
		bottom2 = _ghosts[i]->position->Y + (_ghosts[i]->sourceRect->Height - 4);
		left2 = _ghosts[i]->position->X;
		right2 = _ghosts[i]->position->X + (_ghosts[i]->sourceRect->Width - 4);
		top2 = _ghosts[i]->position->Y;

		if ((bottom1 > top2) && (top1 < bottom2) && (right1 > left2) && (left1 < right2)) {
			Audio::Play(_death);
			Audio::Stop(_beginning);
			_pacman->_isDead = true;
			i = GHOSTCOUNT;
		}
	}
}



void Pacman::CheckDeadGhostCollisions() {
	int i = 0;
	int bottom1 = _pacman->position->Y + (_pacman->sourceRect->Height - 4);
	int bottom2 = 0;
	int left1 = _pacman->position->X;
	int left2 = 0;
	int right1 = _pacman->position->X + (_pacman->sourceRect->Width - 4);
	int right2 = 0;
	int top1 = _pacman->position->Y;
	int top2 = 0;

	for (i = 0; i < GHOSTCOUNT; i++)
	{
		bottom2 = _deadGhost[i]->position->Y + (_deadGhost[i]->sourceRect->Height - 4);
		left2 = _deadGhost[i]->position->X;
		right2 = _deadGhost[i]->position->X + (_deadGhost[i]->sourceRect->Width - 4);
		top2 = _deadGhost[i]->position->Y;

		if ((bottom1 > top2) && (top1 < bottom2) && (right1 > left2) && (left1 < right2)) {
			Audio::Play(_eatGhost);
			_deadGhost[i]->position = new Vector2((Graphics::GetViewportWidth() / 2), (Graphics::GetViewportHeight() / 2));
			_ghostIsEaten = true;
			score += 100;
			if (ScoreChecker == 400)
			{
				_deadGhost[i]->position = new Vector2((rand() % Graphics::GetViewportWidth()), (rand() % Graphics::GetViewportHeight()));
			}
			ScoreChecker += 100;
			cout << ScoreChecker << endl;
			//Audio::Stop(_beginning);
			//_pacman->_isDead = true;
			i = GHOSTCOUNT;
		}
	}
}




void Pacman::CheckCherryCollisions() {
	int i = 0;
	int bottom1 = _pacman->position->Y + (_pacman->sourceRect->Height - 14);
	int bottom2 = 0;
	int left1 = _pacman->position->X;
	int left2 = 0;
	int right1 = _pacman->position->X + (_pacman->sourceRect->Width - 12);
	int right2 = 0;
	int top1 = _pacman->position->Y;
	int top2 = 0;


	for (int i = 0; i < CHERRYCOUNT; i++)
	{
		bottom2 = _cherryMunchie[i]->Position->Y + (_cherryMunchie[i]->Rect->Height - 14);
		left2 = _cherryMunchie[i]->Position->X;
		right2 = _cherryMunchie[i]->Position->X + (_cherryMunchie[i]->Rect->Width - 14);
		top2 = _cherryMunchie[i]->Position->Y;

		if ((bottom1 > top2) && (top1 < bottom2) && (right1 > left2) && (left1 < right2)) {
			Audio::Play(_eatfruit);
			_cherryMunchie[i]->Position->Y = 10000 + (i * 10);
			_cherryMunchie[i]->Position->X = 10000 + (i * 10);
			score += 50;
			_chaseGhost = true;
			ScoreChecker = 0;
			//Timer();
			i = CHERRYCOUNT;
		}
	}
}
void Pacman::CheckMunchieCollisions() {
	int i = 0;
	int bottom1 = _pacman->position->Y + (_pacman->sourceRect->Height - 14);
	int bottom2 = 0;
	int left1 = _pacman->position->X;
	int left2 = 0;
	int right1 = _pacman->position->X + (_pacman->sourceRect->Width - 12);
	int right2 = 0;
	int top1 = _pacman->position->Y;
	int top2 = 0;


	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		bottom2 = _munchie[i]->Position->Y + (_munchie[i]->Rect->Height - 14);
		left2 = _munchie[i]->Position->X;
		right2 = _munchie[i]->Position->X + (_munchie[i]->Rect->Width - 14);
		top2 = _munchie[i]->Position->Y;

		if ((bottom1 > top2) && (top1 < bottom2) && (right1 > left2) && (left1 < right2)) {
			Audio::Play(_eatfruit);
			_munchie[i]->Position->Y = 10000 + (i * 10);
			_munchie[i]->Position->X = 10000 + (i * 10);
			score += 10;
			i = MUNCHIECOUNT;
		}
	}
}


void Pacman::CheckMapCollisions() {
	int i = 0;
	int bottom1 = _pacman->position->Y + (_pacman->sourceRect->Height - 2);
	int bottom2 = 0;
	int left1 = _pacman->position->X;
	int left2 = 0;
	int right1 = _pacman->position->X + (_pacman->sourceRect->Width - 2);
	int right2 = 0;
	int top1 = _pacman->position->Y;
	int top2 = 0;

	for (int i = 0; i < BLOCKS; i++)
	{
		bottom2 = _square[i]->Position->Y + (_square[i]->rect->Height - 2);
		left2 = _square[i]->Position->X;
		right2 = _square[i]->Position->X + (_square[i]->rect->Width - 2);
		top2 = _square[i]->Position->Y;

		if ((bottom1 > top2) && (top1 < bottom2) && (right1 > left2) && (left1 < right2))
		{
			if (_pacman->Direction == 2)
			{
				_pacman->position->X = right2 + 1;
			}
			if (_pacman->Direction == 4)
			{
				_pacman->position->X = _square[i]->Position->X - (_square[i]->rect->Width - 2);
			}
			if (_pacman->Direction == 3)
			{
				_pacman->position->Y = bottom2;
			}
			if (_pacman->Direction == 1)
			{
				_pacman->position->Y = _square[i]->Position->Y - (_square[i]->rect->Height - 2);
			}
			i = BLOCKS;
		}
	}
}


void Pacman::CheckMapGhostCollisions(MovingEnemy* ghost) {
	int i = 0;
	int bottom2 = 0;
	int left2 = 0;
	int right2 = 0;
	int top2 = 0;
	int bottom1 = ghost->position->Y + (ghost->sourceRect->Height - 4);
	int left1 = ghost->position->X;
	int right1 = ghost->position->X + (ghost->sourceRect->Width - 4);
	int top1 = ghost->position->Y;
	for (int i = 0; i < BLOCKS; i++)
	{
		bottom2 = _square[i]->Position->Y + (_square[i]->rect->Height - 2);
		left2 = _square[i]->Position->X;
		right2 = _square[i]->Position->X + (_square[i]->rect->Width - 2);
		top2 = _square[i]->Position->Y;
		if ((bottom1 > top2) && (top1 < bottom2) && (right1 > left2) && (left1 < right2))
		{
			if (ghost->direction == 2)
			{
				ghost->position->X = right2 + 1;
				while (ghost->direction == 2)
				{
					ghost->direction = (rand() % 4) + 1;					
				}
				continue;
			}
			if (ghost->direction == 4)
			{
				ghost->position->X = _square[i]->Position->X - _square[i]->rect->Width;
				while (ghost->direction == 4)
				{
					ghost->direction = (rand() % 4) + 1;
				}
				continue;
			}
			if (ghost->direction == 3)
			{
				ghost->position->Y = bottom2;
				while (ghost->direction == 3)
				{
					ghost->direction = (rand() % 4) + 1;
				}
				continue;
			}
			if (ghost->direction == 1)
			{
				ghost->position->Y = _square[i]->Position->Y - _square[i]->rect->Height;
				while (ghost->direction == 1)
				{
					ghost->direction = (rand() % 4) + 1;
				}
				continue;
			}
			//i = BLOCKS;
		}
	}
}
void Pacman::CheckMapDeadGhostCollisions(DeadGhost* ghost) {
	int i = 0;
	int bottom2 = 0;
	int left2 = 0;
	int right2 = 0;
	int top2 = 0;
	int bottom1 = ghost->position->Y + (ghost->sourceRect->Height - 4);
	int left1 = ghost->position->X;
	int right1 = ghost->position->X + (ghost->sourceRect->Width - 4);
	int top1 = ghost->position->Y;
	for (int i = 0; i < BLOCKS; i++)
	{
		bottom2 = _square[i]->Position->Y + (_square[i]->rect->Height - 2);
		left2 = _square[i]->Position->X;
		right2 = _square[i]->Position->X + (_square[i]->rect->Width - 2);
		top2 = _square[i]->Position->Y;
		if ((bottom1 > top2) && (top1 < bottom2) && (right1 > left2) && (left1 < right2))
		{
			if (ghost->direction == 2)
			{
				ghost->position->X = right2 + 1;
				while (ghost->direction == 2)
				{
					ghost->direction = (rand() % 4) + 1;					
				}
				continue;
			}
			if (ghost->direction == 4)
			{
				ghost->position->X = _square[i]->Position->X - _square[i]->rect->Width;
				while (ghost->direction == 4)
				{
					ghost->direction = (rand() % 4) + 1;
				}
				continue;
			}
			if (ghost->direction == 3)
			{
				ghost->position->Y = bottom2;
				while (ghost->direction == 3)
				{
					ghost->direction = (rand() % 4) + 1;
				}
				continue;
			}
			if (ghost->direction == 1)
			{
				ghost->position->Y = _square[i]->Position->Y - _square[i]->rect->Height;
				while (ghost->direction == 1)
				{
					ghost->direction = (rand() % 4) + 1;
				}
				continue;
			}
			//i = BLOCKS;
		}
	}
}


void Pacman::CheckGameOver(Input::KeyboardState* state, Input::Keys restartKey)
{
	if (state->IsKeyDown(Input::Keys::R) && !_restartKey)
	{
		_restartKey = true;
		Dead();
		_gameOver = false;
		_isInGame = true;
		_pacman->_isDead = false;
	}
	if (state->IsKeyUp(restartKey)) {
		_restartKey = false;
	}
}




void Pacman::CheckPaused(Input::KeyboardState* state, Input::Keys pauseKey) {
	if (state->IsKeyDown(Input::Keys::P) && !_pKeyDown)
	{
		_pKeyDown = true;

		_paused = !_paused;
		if (_paused) {
			Audio::Pause(_beginning);
		}
		else {
			Audio::Resume(_beginning);
		}	
	}
	if (state->IsKeyUp(Input::Keys::P))
		_pKeyDown = false;

}
void Pacman::CheckInGame(Input::KeyboardState* state, Input::Keys StartKey) {
	
	if (state->IsKeyDown(StartKey) && !_SkeyDown)
	{
		_SkeyDown = true;
		_isInGame = !_isInGame;
		Audio::Stop(_inGame);
		if(!Audio::Play(_beginning))
			Audio::Play(_beginning);
	}
	if (state->IsKeyUp(StartKey))
		_SkeyDown = false;
}


void Pacman::CheckViewportCollision() {
	_pacman->sourceRect->X = _pacman->sourceRect->Width * _pacman->frame;

	if (_pacman->position->X + _pacman->sourceRect->Width > 1051) {
		_pacman->position->X = -32 + _pacman->sourceRect->Width;
	}
	if (_pacman->position->X + _pacman->sourceRect->Width < 5) {
		_pacman->position->X = 1024 - _pacman->sourceRect->Width;
	}
	if (_pacman->position->Y + _pacman->sourceRect->Height < 5) {
		_pacman->position->Y = 770 - _pacman->sourceRect->Height;
	}
	if (_pacman->position->Y + _pacman->sourceRect->Height > 797) {
		_pacman->position->Y = -32 + _pacman->sourceRect->Height;
	}
	_pacman->sourceRect->Y = _pacman->sourceRect->Height * _pacman->Direction;



}






void Pacman::UpdatePacman(int elapsedTime) {
	_pacman->currentFrameTime += elapsedTime;


	if (_pacman->currentFrameTime > _cPacmanFrameTime) {
		_pacman->frame++;
		if (_pacman->frame >= 2) {
			_pacman->frame = 0;
		}
		_pacman->currentFrameTime = 0;
	}
}

void Pacman::UpdateGhost(MovingEnemy* ghost, int elapsedTime, float& pacmanX, float& pacmanY, int& pacmanDir) {

	if (ghost->direction == 4) {
		ghost->position->X += ghost->speed * elapsedTime;//right
		//ghost->sourceRect = new Rect(0.0f, 0.0f, 32, 32);
	}
	else if (ghost->direction == 2)
	{
		ghost->position->X += -ghost->speed * elapsedTime;//left
		//ghost->sourceRect = new Rect(32, 0.0f, 32, 32);
	}
	else if (ghost->direction == 1) {
		ghost->position->Y += ghost->speed * elapsedTime;//DOWN
	}
	else if (ghost->direction == 3)
	{
		ghost->position->Y += -ghost->speed * elapsedTime;//UP
	}
	//else if (ghost->direction == 0)
	//{
	//	ghost->position->Y = ghost->position->Y;
	//	ghost->position->X = ghost->position->X;
	//}

	int distanceX = pacmanX - ghost->position->X;
	int distanceY = pacmanY - ghost->position->Y;

	bool Xgreater = abs(distanceX) > abs(distanceY);

	//if (Xgreater) {
	//	if(pacmanX < ghost->position->X)
	//	{
	//		ghost->direction = 2;
	//	}
	//	else
	//	{
	//		ghost->direction = 4;
	//	}
	//}
	//else
	//{
	//	if (pacmanY < ghost->position->Y) 
	//	{
	//		ghost->direction = 3;
	//	}
	//	else
	//	{
	//		ghost->direction = 1;
	//	}
	//}

	
	ghost->sourceRect->Y = ghost->sourceRect->Height * ghost->direction;

}

void Pacman::UpdateDeadGhost(DeadGhost* ghost, int elapsedTime, float& pacmanX, float& pacmanY, int& pacmanDir) {

	if (ghost->direction == 4) {
		ghost->position->X += ghost->speed * elapsedTime;//right
		//ghost->sourceRect = new Rect(0.0f, 0.0f, 32, 32);
	}
	else if (ghost->direction == 2)
	{
		ghost->position->X += -ghost->speed * elapsedTime;//left
		//ghost->sourceRect = new Rect(32, 0.0f, 32, 32);
	}
	else if (ghost->direction == 1) {
		ghost->position->Y += ghost->speed * elapsedTime;//DOWN
	}
	else if (ghost->direction == 3)
	{
		ghost->position->Y += -ghost->speed * elapsedTime;//UP
	}
	//else if (ghost->direction == 0)
	//{
	//	ghost->position->Y = ghost->position->Y;
	//	ghost->position->X = ghost->position->X;
	//}

	int distanceX = (Graphics::GetViewportWidth() / 2) - ghost->position->X;
	int distanceY = (Graphics::GetViewportHeight() / 2) - ghost->position->Y;

	bool Xgreater = abs(distanceX) > abs(distanceY);

	//if (_ghostIsEaten) {
	//	if (Xgreater) {

	//		if ((Graphics::GetViewportWidth() / 2) < ghost->position->X)
	//		{
	//			ghost->direction = 2;
	//		}
	//		else
	//		{
	//			ghost->direction = 4;
	//		}
	//	}
	//	else
	//	{
	//		if ((Graphics::GetViewportHeight() / 2) < ghost->position->Y)
	//		{
	//			ghost->direction = 3;
	//		}
	//		else
	//		{
	//			ghost->direction = 1;
	//		}
	//	}

	//}
	if (_ghostIsEaten)
	{
		if (ghost->position = new Vector2((Graphics::GetViewportWidth() / 2), (Graphics::GetViewportHeight() / 2)))
		{
			_ghostIsEaten = false;
		}
	}


	
	ghost->sourceRect->Y = ghost->sourceRect->Height * ghost->direction;

}






void Pacman::UpdateMuchies(Enemy* munchie, int elapsedTime) {

	munchie->CurrentFrameTime += elapsedTime;


	if (munchie->CurrentFrameTime > _cMunchieFrameTime) {
		munchie->_frameCount++;

		if (munchie->_frameCount >= 2) {
			munchie->_frameCount = 0;

		}
		munchie->CurrentFrameTime = 0;
		munchie->Rect->X = munchie->Rect->Width * munchie->_frameCount;
	}


}


void Pacman::UpdateCherry(int elapsedTime) {
	for (int i = 0; i < CHERRYCOUNT; i++)
	{
		_cherryMunchie[i]->CurrentFrameTime += elapsedTime;


		if (_cherryMunchie[i]->CurrentFrameTime > _cCherryFrameTime) {
			_cherryMunchie[i]->_frameCount++;

			if (_cherryMunchie[i]->_frameCount >= 2) {
				_cherryMunchie[i]->_frameCount = 0;

			}
			_cherryMunchie[i]->CurrentFrameTime = 0;
			_cherryMunchie[i]->Rect->X = _cherryMunchie[i]->Rect->Width * _cherryMunchie[i]->_frameCount;

		}
	}

}

void Pacman::UpdateDeadGhost(int elapsedTime) {
	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		_deadGhost[i]->currentFrameTime += elapsedTime;


		if (_deadGhost[i]->currentFrameTime > _cCherryFrameTime) {
			_deadGhost[i]->_frameCount++;

			if (_deadGhost[i]->_frameCount >= 2) {
				_deadGhost[i]->_frameCount = 0;

			}
			_deadGhost[i]->currentFrameTime = 0;
			_deadGhost[i]->sourceRect->X = _deadGhost[i]->sourceRect->Width * _deadGhost[i]->_frameCount;

		}
	}

}