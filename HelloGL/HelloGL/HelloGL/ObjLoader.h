#pragma once
#include "Texture2D.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>


namespace ObjLoader
{
	Obj* Load(char* path);
	//TexturedMesh* LoadTextured(char* path);
};
