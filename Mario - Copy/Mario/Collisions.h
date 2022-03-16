#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "Commons.h"
#include "TileLayer.h"
#include "LevelMap.h"
#include "Engine.h"

#include <vector>
#include <iostream>
using namespace std;


class Character;

class Collisions 
{
public:
int m_level;
	~Collisions();
	static Collisions* Instance() { return m_instance = (m_instance != nullptr) ? m_instance : new Collisions(); }



	bool CheckCollision(SDL_Rect obj1, SDL_Rect obj2);
	bool Circle(Character* character1, Character* character2);
	bool MapCollision(SDL_Rect obj1);

private:
	Collisions();
	TileMap m_CollisionTileMap;// our matrix wher we have our tile ID's, in order to make sure the player is hitting the wall, we want to check if the tileID is different from 0
	TileLayer* m_CollisionLayer;// we also need collision layer because we have more than one layer e.g Background and foreGround// we can do it for this for all layer we just need to do a loop to check for each layer
	static Collisions* m_instance;

	
};
