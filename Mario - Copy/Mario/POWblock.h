#pragma once
#include "GameScreenLevel1.h"


class LevelMap;


class POWblock
{
public:
	POWblock(SDL_Renderer* renderer, LevelMap* levelmap);
	~POWblock();
	void Render();
	Rect2D GetCollisionBox() {
		return Rect2D(m_position.X, m_position.Y, m_single_sprite_w, m_single_sprite_h);
	}

	void TakeHit();
	bool IsAvailable() { return m_num_hits_left > 0; }


private:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	LevelMap* m_level_map;

	float m_single_sprite_w;
	float m_single_sprite_h;
	int m_num_hits_left;

};



