#pragma once
#include "Layer.h"
#include "LevelMap.h"
#include "TextureAnim.h"



using TileSetList = vector<TileSet>;
using TileMap = vector<vector<int>>;

class TileLayer : public Layer
{
public:
	TileLayer(int TileSize, int rowcount, int columncount, TileMap tilemap, TileSetList tilesets);
	virtual void Render();
	virtual void Update();
	inline TileMap GetTileMap() { return m_TileMap; }
	inline int GetTileSize() { return m_TileSize; }
	inline int GetWidth() { return m_ColumnCount * m_TileSize; }
	inline int GetHeight() { return m_RowCount * m_TileSize; }

	~TileLayer();

private:
	int m_TileSize;
	int m_RowCount, m_ColumnCount;
	TileMap m_TileMap;
	TileSetList m_Tilesets;
};

