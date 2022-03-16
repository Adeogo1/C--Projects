#include "MeshLoader.h"

#include <iostream>
#include <fstream>

using namespace std;

namespace MeshLoader
{
	void LoadVertices(ifstream& inFile, Mesh& mesh);
	void LoadNormals(ifstream& inFile, Mesh& mesh);//normal is the same as colours you just change the name
	void LoadTexCoords(ifstream& inFile, Mesh& mesh);
	void LoadIndices(ifstream& inFile, Mesh& mesh);

	void LoadVertices(ifstream& inFile, Mesh& mesh)
	{


		inFile >> mesh.VertexCount;

		if (mesh.VertexCount > 0)
		{
			mesh.Vertices = new Vertex[mesh.VertexCount];

			for (int i = 0; i < mesh.VertexCount; i++)
			{
				inFile >> mesh.Vertices[i].x;
				inFile >> mesh.Vertices[i].y;
				inFile >> mesh.Vertices[i].z;
			}
		}
	}

	void LoadNormals(ifstream& inFile, Mesh& mesh)
	{
		//TODO: LOAD COLOURS
		inFile >> mesh.NormalCount;
		if (mesh.NormalCount > 0)
		{
			mesh.Normals = new  Vector3[mesh.NormalCount];
			for (int i = 0; i < mesh.NormalCount; i++)
			{
				inFile >> mesh.Normals[i].x;// colours
				inFile >> mesh.Normals[i].y;
				inFile >> mesh.Normals[i].z;
			}
		}
	}

	void LoadTexCoords(ifstream& inFile, Mesh& mesh)
	{
		//TODO: Load TexCoords

		inFile >> mesh.TexCoordCount;
		if (mesh.TexCoordCount > 0)
		{
			mesh.TexCoord = new TexCoord[mesh.TexCoordCount];
			for (int i = 0; i < mesh.TexCoordCount; i++)
			{
				inFile >> mesh.TexCoord[i].u;
				inFile >> mesh.TexCoord[i].v;

			}
		}
	}

	void LoadIndices(ifstream& inFile, Mesh& mesh)
	{
		//TODO: Load Indices
		inFile >> mesh.IndexCount;
		if (mesh.IndexCount > 0)
		{
			mesh.Indices = new GLushort[mesh.IndexCount];
			for (int i = 0; i < mesh.IndexCount; i++)
			{
				inFile >> mesh.Indices[i];
			}
		}
	}

	Mesh* MeshLoader::Load(char* path)
	{
		Mesh* mesh = new Mesh();

		ifstream inFile;//ignore it

		inFile.open(path);
		//inFileBin.open(path, ios::binary);

		if (!inFile.good())
		{
			cerr << "Can't open texture file " << path << endl;
			return nullptr;
		}

		//LOAD DATA USING METHODS ABOVE
		
		LoadVertices(inFile, *mesh);
		LoadTexCoords(inFile, *mesh);
		LoadNormals(inFile, *mesh);
		
		LoadIndices(inFile, *mesh);
		
		inFile.close();

		return mesh;
		
	}

	//TexturedMesh* MeshLoader::LoadTextured(char* path)
	//{
	//	TexturedMesh* mesh = new TexturedMesh();
	//	mesh->Mesh = new Mesh();

	//	//LOAD FILE AND DATA

	//	return mesh;
	//}
}