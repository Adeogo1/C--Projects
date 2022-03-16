#include "POWblock.h"






POWblock::POWblock(SDL_Renderer* renderer, LevelMap* levelmap)
{
	string imagePath = "Images/PowBlock.png";
	m_texture = new Texture2D(renderer);
	if (!m_texture->LoadTextureFromFile(imagePath.c_str()))
	{
		cout << "Failed to load Texture." << endl;
		return;
	}
	m_level_map = levelmap;
	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();
	m_num_hits_left = 3;
	m_position = Vector2D((SCREEN_WIDTH * 0.5f) - m_single_sprite_w * 0.5f, 260);
}



void POWblock::Render() {
	//if (m_num_hits_left > 0)
	//{
	//	// get the portion of the sheet we want to draw
	//	int left = m_single_sprite_w * (m_num_hits_left - 1);

	//								//xPos, yPos, sprite sheet width, sprite sheet height
	//	SDL_Rect portion_of_sprite = { left, 0, m_single_sprite_w, m_single_sprite_h };
	//	SDL_Rect dest_rect = { static_cast<int>(m_position.X), static_cast<int>(m_position.Y), m_single_sprite_w,m_single_sprite_h };

	//	//draw the sprite
	//	m_texture->Renderer(portion_of_sprite, dest_rect, SDL_FLIP_NONE);
	//}
}



void POWblock::TakeHit() 
{
	//m_num_hits_left--;
	//if (m_num_hits_left <= 0)
	//{
	//	m_num_hits_left = 0;
	//	m_level_map->ChangeTileAt(8, 7, 0);
	//	m_level_map->ChangeTileAt(8, 7, 0);
	//}
}









POWblock::~POWblock()
{
	m_renderer = nullptr;
	delete m_texture;
	m_texture = nullptr;
	m_level_map = nullptr;
}