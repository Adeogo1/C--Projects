#include "CharacterLuigi.h"





//CharacterLuigi::CharacterLuigi(Properties* props) : Character(props) {
//	//m_current_level_map = map;
//}
//
//
//void CharacterLuigi::Update(float deltaTime) {
//	int centralX_position = (int)(m_position.X + (m_texture->GetWidth() * 0.5)) / TILE_WIDTH;
//	int foot_position = (int)(m_position.Y + m_texture->GetHeight()) / TILE_HEIGHT;
//
//	//switch (e.type) {
//	//case SDL_KEYDOWN:
//	//	printf("Key press detected\n");
//	//	switch (e.key.keysym.sym)
//	//	{
//	//	case SDLK_a:
//	//	{
//	//		printf("left press detected\n");
//	//		m_moving_left = true;
//	//		break;
//	//	}
//	//	case SDLK_d:
//	//	{
//	//		printf("right press detected\n");
//	//		m_moving_right = true;
//	//		break;
//	//	}
//	//	case SDLK_w:
//	//	{
//	//		printf("up press detected\n");
//	//		if (m_canJump) {
//	//			Jump();
//	//		}
//
//	//		break;
//	//	}
//	//	}
//	//	break;
//
//	//case SDL_KEYUP:
//	//	printf("Key release detected\n");
//	//	switch (e.key.keysym.sym)
//	//	{
//	//	case SDLK_a:
//	//	{
//	//		printf("left release detected\n");
//	//		m_moving_left = false;
//	//		break;
//	//	}
//	//	case SDLK_d:
//	//	{
//	//		printf("right release detected\n");
//	//		m_moving_right = false;
//	//		break;
//	//	}
//	//	case SDLK_w:
//	//	{
//	//		printf("up release detected\n");
//	//		//m_isJumping = false;
//	//		break;
//	//	}
//	//	}
//	//	break;
//	//	/*case SDL_MOUSEMOTION:
//	//		int x,y;
//	//		SDL_GetMouseState(&x, &y);
//	//		if (x < m_position.x) {
//	//			MoveRight(deltaTime);
//	//		}
//	//		if (x > m_position.x) {
//	//			MoveRight(deltaTime);
//	//		}*/
//	//default:
//	//	break;
//	//}
//
//
//
//	if (m_current_level_map->GetTileAt(foot_position, centralX_position) == 0)
//	{
//		AddGravity(deltaTime);
//	}
//	else
//	{
//		m_canJump = true;
//	}
//
//
//	Character::Update(deltaTime);
//}
//
//void CharacterLuigi::AddGravity(float deltaTime) {
//	if (m_position.Y + 64 <= SCREEN_HEIGHT) {
//		m_position.Y += GRAVITY * deltaTime;
//
//	}
//	else
//	{
//		m_canJump = true;
//	}
//}
//
//CharacterLuigi::~CharacterLuigi() {
//
//}
