#include "GameScreen.h"
#include "Commons.h"


GameScreen::GameScreen(SDL_Renderer* renderer) {
	m_renderer = renderer;
}


void GameScreen::Update(float deltaTime) {

}


void GameScreen::Render() {

}



GameScreen::~GameScreen() {

	m_renderer = nullptr;
	delete m_renderer;
}