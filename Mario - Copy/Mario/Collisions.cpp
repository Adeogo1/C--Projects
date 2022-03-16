#include "Collisions.h"
#include "Character.h"




// initialise instance to nullptr
Collisions* Collisions::m_instance = nullptr;

Collisions::Collisions() {
	m_level = 0;
	if (m_level == 1) {
		m_CollisionLayer = (TileLayer*)Engine::GetInstance()->GetMap()->GetMapLayers().back();		//the level map takes a vector of layers not tile layers, since Tile Layers are inheriting from layers we want to pass the return values of GetLayer to tile layer
	//the line above get the map then the layers// also we are using back because the collision is in the foreground which is above the background in the tmx file it would be back() if we did the other way round
	}
	else if (m_level == 2) {
		m_CollisionLayer = (TileLayer*)Engine::GetInstance()->GetMap2()->GetMapLayers().back();		//the level map takes a vector of layers not tile layers, since Tile Layers are inheriting from layers we want to pass the return values of GetLayer to tile layer
	//the line above get the map then the layers// also we are using back because the collision is in the foreground which is above the background in the tmx file it would be back() if we did the other way round
	}
	//now to get the tile map inside of that layer
	m_CollisionTileMap = m_CollisionLayer->GetTileMap();
}

bool Collisions::CheckCollision(SDL_Rect obj1, SDL_Rect obj2) {
	//bool x_overLaps = (obj1.x < obj2.x + obj2.w) && (obj1.x + obj1.w > obj2.x);
	//bool y_overLaps = (obj1.y < obj2.y + obj2.h) && (obj1.y + obj1.h > obj2.y);
	//return (x_overLaps && y_overLaps);
	if (obj1.x + (obj1.w / 2) > obj2.x && obj1.x + (obj1.w / 2) < obj2.x + obj2.w && obj1.y + (obj1.h / 2) > obj2.y && obj1.y + (obj1.h / 2) < obj2.y + obj2.h) {
		return true;
	}
	return false;
}

bool Collisions::Circle(Character* character1, Character* character2) {
	Vector2D vec = Vector2D((character1->GetPosition()->X - character2->GetPosition()->X), (character1->GetPosition()->Y - character2->GetPosition()->Y));
	double distance = sqrt((vec.X * vec.X) + (vec.Y * vec.Y));


	//double combined_Distance = (character1->GetCollisionRadius() + character2->GetCollisionRadius());
	double combined_Distance = (character1->GetCollisionRadius() + character2->GetCollisionRadius());
	return distance < combined_Distance;
}


//bool Collisions::CircleColliders(CircleCollider circleCollider, CircleCollider circleCollider2) {
//	Vector2D vec = Vector2D((circleCollider.x - circleCollider2.x), (circleCollider.y - circleCollider2.y));
//	double distance = sqrt((vec.X * vec.X) + (vec.Y * vec.Y));
//
//	double combined_Distance = (circleCollider.radius + circleCollider2.radius);
//	return distance < combined_Distance;
//}



bool Collisions::MapCollision(SDL_Rect obj1) {//checks if an object overlaps with map
	int tilesize = 32;
	int RowCount = 23;//change it when you make map bigger
	int ColCount = 240;// change it when you make map bigger

	int left_tile = obj1.x / tilesize;
	int right_tile = (obj1.x + obj1.w) / tilesize;
	int top_tile = obj1.y / tilesize;
	int bottom_tile = (obj1.y + obj1.h) / tilesize;			//all of this is just to make sure we take this rect and check for the tile all sides of the tile
	if (left_tile < 0) left_tile = 0;
	if (right_tile > ColCount) right_tile = ColCount;

	if (top_tile < 0) top_tile = 0;
	if (bottom_tile > RowCount) bottom_tile = RowCount;

	for (int i = left_tile; i <= right_tile; ++i)
	{
		for (int j = top_tile; j <= bottom_tile; ++j)//if the value of the tile map is greater than zero then we have a collision
		{
			if (m_CollisionTileMap[j][i] > 0)
			{
				return true;
			}
		}
	}

	return false;
}


Collisions::~Collisions() 
{
	delete m_instance;
	m_instance = nullptr;
	delete m_CollisionLayer;
	m_CollisionLayer = nullptr;
}

