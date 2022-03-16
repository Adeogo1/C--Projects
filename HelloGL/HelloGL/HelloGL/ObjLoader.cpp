#include "ObjLoader.h"


#include <iostream>
#include <string>
#include <fstream>

using namespace std;




namespace ObjLoader
{

	void loadObj(ifstream& inFile, Obj* obj);

	void loadObj(ifstream& inFile, Obj* obj) {
		obj->Indicies = 0;
		string line = "";
		string prefix = "";
		stringstream ss;
		float LargestX = 0;
		float SmallestX = 0;
		while (getline(inFile, line))//(!inFile.eof())
		{
			inFile >> prefix;
			ss.clear();
			ss.str(line);
			if (prefix == "v")
			{
				Vector3 tempVertx;
				inFile >> tempVertx.x;
				inFile >> tempVertx.y;
				inFile >> tempVertx.z;
				if (LargestX < tempVertx.x)
				{
					LargestX = tempVertx.x;
				}
				if (SmallestX > tempVertx.x)
				{
					SmallestX = tempVertx.x;
				}

				obj->vertex.push_back(tempVertx);
			}
			else if (prefix == "vt")
			{
				Vector2 tempVertx;
				inFile >> tempVertx.x;
				inFile >> tempVertx.y;

				obj->TexCoord.push_back(tempVertx);
			}
			else if (prefix == "vn")
			{
				Vector3 tempVertx;
				inFile >> tempVertx.x;
				inFile >> tempVertx.y;
				inFile >> tempVertx.z;

				obj->Normals.push_back(tempVertx);
			}
			else if (prefix == "f") {
				int counter = 0;

				obj->Indicies += 3;
				char extrachar;
				GLushort index;
				/*GLint temp = 0;
				while (inFile >> temp)
				{
					obj->Indicies += 3;
					if (counter == 0)
					{
						obj->Vertices.push_back(temp - 1);
					}
					else if (counter == 1)
					{
						obj->TexCoordsindices.push_back(temp -1);
					}
					else if (counter == 2)
					{
						obj->Normalindicies.push_back(temp - 1);
					}

					if (ss.peek() == '/')
					{
						++counter;
						ss.ignore(1, '/');
					}
					else if (ss.peek() == ' ')
					{
						++counter;
						ss.ignore(1, ' ');
					}
					if (counter > 2)
					{
						counter = 0;
					}
				}*/

				for (int i = 0; i < 3; i++)
				{

					inFile >> index;
					inFile >> extrachar;
					obj->Vertices.push_back(index - 1);
					
					inFile >> index;
					inFile >> extrachar;
					obj->TexCoordsindices.push_back(index - 1);

					inFile >> index;
					obj->Normalindicies.push_back(index - 1);

				}
			}
		}

		cout << "largest x" << LargestX << "  " <<"smallest x" << SmallestX<< endl;		

	}





	Obj* Load(char* path)
	{
		Obj* obj = new Obj();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.is_open())
		{
			cout << "ERROR::OBJLOADER::Could not open file";
		}

		loadObj(inFile, obj);

		inFile.close();

		return obj;

	}
}