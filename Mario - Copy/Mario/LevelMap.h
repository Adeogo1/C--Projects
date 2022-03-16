#pragma once
#ifndef _LEVELMAP_H
#define _LEVELMAP_H
#include "Constants.h"
#include "Layer.h"


class LevelMap
{
public:
	LevelMap(){}
	void Render();//renders our layers
	void Update();
	void Clean();
	vector<Layer*> GetMapLayers() { return m_MapLayers; }

	~LevelMap();

private:
	friend class MapParser;
	vector<Layer*>m_MapLayers;
};




#endif // !_LEVELMAP_H