#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
//#include <windows.h>//reading data from the bitmap file
#include "GL/freeglut.h"
#include "GLUTCallbacks.h"
#include "Structure.h"
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;



class Texture2D
{
public:
	Texture2D();
	~Texture2D();

	bool LoadRAW(char* path, int width, int height);
	bool Load2PNG(char* path, int width, int height);
	//bool LoadBMP(char* path, int width, int height);
	//void loadBitMap(char* fileName, char* outFileName);
	//bool loadOBJ(const char* path, vector < Vector3 >& out_vertices, vector < Vector2 >& out_uvs, vector < Vector3 >& out_normals);
	//bool LoadTGA(char* path, int width, int height);
	GLuint GetID() const { return _ID; }
	int GetWidth() const { return _width; }
	int GetHeight() const { return _height; }


private:

	GLuint _ID;
	int _width, _height;
	char* _Cwidth;
	char* _Cheight;
	BITMAPFILEHEADER bfh;//use these to read data from thr file//contains info about file, format and other things
	//BITMAPINFOHEADER bih;
	BITMAPINFOHEADER bitMapInfo;
};



