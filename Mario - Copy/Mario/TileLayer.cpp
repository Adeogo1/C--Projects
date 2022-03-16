#include "TileLayer.h"




TileLayer::TileLayer(int TileSize, int rowcount, int columncount, TileMap tilemap, TileSetList tilesets) : m_TileSize(TileSize), m_ColumnCount(columncount), m_RowCount(rowcount), m_TileMap(tilemap), m_Tilesets(tilesets)
{

	for (unsigned int i = 0; i < m_Tilesets.size(); i++)
	{
		TextureAnim::GetInstance()->LoadTexture(m_Tilesets[i].Name, "Assets/Maps/" + m_Tilesets[i].Source);
	}

}


void TileLayer::Render() {
	for (unsigned int i = 0; i < m_RowCount; i++)
	{
		for (unsigned int j = 0; j < m_ColumnCount; j++)
		{
			int tileID = m_TileMap[i][j];
			if (tileID == 0)
			{
				continue;
			}
			else//if we have a tile ID that is not 0 (something that can be drawn on the screen)
			{
				//our map has more than 1 tileset, the ID of the first tileset is 1. W e want to know from which tile set is this tile coming from
				//hence why we need an index which is going to be setting the value of the current tile. The index because we have the tileset list
				int Index = 0;
				if (m_Tilesets.size() > 1)// we're checking do we only have one tileset, if true then we dont need to transform the IDs
				{
					for (unsigned int k = 0; k < m_Tilesets.size(); k++)
					{
						if (tileID >= m_Tilesets[k].First && tileID <= m_Tilesets[k].Last)//(tileID > m_Tilesets[k].First && tileID < m_Tilesets[k].Last)
						{
							tileID = tileID + m_Tilesets[k].TileCount - m_Tilesets[k].Last;
							Index = k;
							break;
						}
					}
				}

				TileSet ts = m_Tilesets[Index];
				int tileRow = tileID / ts.ColumnCount;
				int tileColumn = tileID - tileRow * ts.ColumnCount - 1;

				//if this tile is on the last column
				if (tileID % ts.RowCount == 0)
				{
					tileRow--;
					tileColumn = ts.ColumnCount - 1;
				}

				TextureAnim::GetInstance()->DrawTile(ts.Name, ts.TileSize, j * ts.TileSize, i * ts.TileSize, tileRow, tileColumn);
			}
		}
	}
}


void TileLayer::Update() {

}


TileLayer::~TileLayer()
{
}