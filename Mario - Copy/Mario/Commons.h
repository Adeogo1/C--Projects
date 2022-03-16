#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <map>

#include <iomanip>
#include <iostream>
using namespace std;


struct CircleCollider
{
	float radius;
	float x;
	float y;
	CircleCollider(float radius, float x, float y) {
		this->radius = radius;
		this->x = x;
		this->y = y;
	}
};


struct Properties
{
public:
	Properties(string textureID, float x, float y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE) {
		X = x;
		Y = y;
		Flip = flip;
		Width = width;
		Height = height;
		TextureID = textureID;
	}
public:
	string TextureID;
	int Width, Height;
	float X, Y;
	SDL_RendererFlip Flip;
};



struct Rect2D
{
	float x;
	float y;
	float width;
	float height;
	Rect2D(float x_pos, float y_pos, float width, float height) {
		x = x_pos;
		y = y_pos;
		this->width = width;
		this->height = height;
	}
};






struct TileSet
{
	int First, Last, RowCount, ColumnCount, TileCount, TileSize;
	string Name, Source;// this nsame will be used by the texture manager// source is the file name
};



enum  SCREENS
{
	SCREEN_INTRO,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_LEVELSELECT,
	SCREEN_GAMEOVER,
	SCREEN_LEVELCOMPLETE,
	SCREEN_HIGHSCORES
};


enum FACING
{
	FACING_LEFT,
	FACING_RIGHT
};

enum Axis {
	HORIZONTAL,
	VERTICAL
};


struct Colours
{
	SDL_Color RED = { 255,0,0,255 };
	SDL_Color GREEN = { 0,255,0,255 };
	SDL_Color BLUE = { 0,0,255,255 };
	SDL_Color LIGHT_PINK = { 255,182,193,255 };
	SDL_Color PINK = { 255,192,203,255 };
	SDL_Color ORCHID = { 218,112,214,255 };
	SDL_Color PURPLE = { 128,0,128,255 };
	SDL_Color INDIGO = { 75,0,130,255 };
	SDL_Color ROYAL_BLUE = { 65,105,225,255 };
	SDL_Color TURQUOISE = { 0,245,255,255 };
	SDL_Color YELLOW = { 255,255,0,255 };
	SDL_Color ORANGE = { 255,165,0,255 };
	SDL_Color BROWN = { 165,42,42,255 };
	SDL_Color BLACK = { 0,0,0,255 };
	SDL_Color WHITE = { 255,255,255,255 };
};