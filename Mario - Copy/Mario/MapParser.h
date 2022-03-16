#pragma once
#include "tinyxml.h"
#include "LevelMap.h"
#include "TileLayer.h"
#include "GameScreen.h"
#include <map>
#include <string>
#include <iostream>
using namespace std;

class MapParser
{
public:

	bool Load(int level);//load map
	void Clean();

	inline LevelMap* GetMap(string ID) { return m_MapDict[ID]; }
	inline static MapParser* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new MapParser(); }

	~MapParser();

private:
	bool Parse(string ID, string source);//id of the map to parse, filename 
	TileSet ParseTileset(TiXmlElement* xmlTileset);// because the map has layers
	TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, TileSetList tilesets, int tilesize, int rowcount, int columncount);//parse tile layers

	MapParser();
	static MapParser* s_Instance;
	map<string, LevelMap* >m_MapDict;//id of the map
	GameScreen* level;
};



