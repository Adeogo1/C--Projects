#include "MapParser.h"

MapParser* MapParser::s_Instance = nullptr;



MapParser::MapParser()
{
}

bool MapParser::Load(int level) {
	
	if (level == 0)
	{
		return (Parse("Level1", "Assets/Maps/Level1Mario.tmx"));//parsing is when one string of data gets converted to another to a different kind of data
	}
	else if (level == 1)
	{
		return (Parse("Level2", "Assets/Maps/Level2Mario.tmx"));//parsing is when one string of data gets converted to another to a different kind of data
	}
}

void MapParser::Clean() {
	map<string, LevelMap*>::iterator it;
	for (it = m_MapDict.begin(); it != m_MapDict.end(); it++)
	{
		it->second = nullptr;
	}
	m_MapDict.clear();
}



bool MapParser::Parse(string ID, string source) {
	//create xml document because this is the guy who takes the source, the xml file and check if that file is correctly opened
	TiXmlDocument xml;
	xml.LoadFile(source);

	if (xml.Error())
	{
		cerr << "Failed to Load : " << source << endl;
		return false;
	}

	TiXmlElement* root = xml.RootElement();
	int rowcount, columncount, tilesize = 0;

	root->Attribute("width", &columncount);
	root->Attribute("height", &rowcount);
	root->Attribute("tilewidth", &tilesize);

	//parse tilesets
	TileSetList tilesets;
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())// we run through all the tileset
	{//you start by the first child and you increment every time to the next element and we make sure that the component we're checking right now is a tileset
		//and we push it in the list that we created 
		if (e->Value() == string("tileset")) {
			tilesets.push_back(ParseTileset(e));
		}
	}

	//parse layers
	int mapSize[MAP_HEIGHT][MAP_WIDTH];
	LevelMap* levelmap = new LevelMap();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == string("layer")) {
			TileLayer* tilelayer = ParseTileLayer(e, tilesets, tilesize, rowcount, columncount);
			levelmap->m_MapLayers.push_back(tilelayer);
		}

	}

	m_MapDict[ID] = levelmap;

	return true;
}

TileSet MapParser::ParseTileset(TiXmlElement* xmlTileset) {
	TileSet tileset;// creates a value that gets the tileset from the xml
	tileset.Name = xmlTileset->Attribute("name");//access the attribute of an xml element//this is for string
	xmlTileset->Attribute("firstgid", &tileset.First);	//this is for numbers

	xmlTileset->Attribute("tilecount", &tileset.TileCount);
	tileset.Last = (tileset.First + tileset.TileCount) - 1;

	xmlTileset->Attribute("columns", &tileset.ColumnCount);
	tileset.RowCount = tileset.TileCount / tileset.ColumnCount;
	xmlTileset->Attribute("tilewidth", &tileset.TileSize);

	TiXmlElement* image = xmlTileset->FirstChildElement();
	tileset.Source = image->Attribute("source");
	return tileset; //we use this to paste our map
}

TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, TileSetList tilesets, int tilesize, int rowcount, int columncount) {
	// we will be parsing the numbers in the map file and coverting it to a 2D tile map
   //tile map in tile layer is a 2d vector and will be taking in the ints for the time map

   //we're trying to make sure that we got the element called data
	TiXmlElement* data = nullptr;

	for (TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		//we check if the name of the component we are on called data
		if (e->Value() == string("data")) {
			//then we take that element and put it in data
			data = e;
			//there is only one data in a map
			break;
		}
	}

	//parse layer tile map
	string matrix(data->GetText());
	istringstream iss(matrix);
	string ID;

	TileMap tileMap(rowcount, vector<int>(columncount, 0));// creating an array which has a matrix a two dimensional array with the first size is this one it has this number of rows and this number of count 

	for (int row = 0; row < rowcount; row++)
	{
		for (int column = 0; column < columncount; column++)
		{
			getline(iss, ID, ',');// the comma is the divider but now that we have the number we will now be converting it to integer
			stringstream convertor(ID);
			convertor >> tileMap[row][column];

			if (!iss.good())// we are checking if we're still good, which means we haven't reached the end of this file
			{
				break;
			}
		}
	}
	return (new TileLayer(tilesize, rowcount, columncount, tileMap, tilesets));
}

MapParser::~MapParser()
{
}