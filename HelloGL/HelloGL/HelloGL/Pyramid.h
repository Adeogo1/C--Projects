#pragma once
#include "SceneObject.h"


class Pyramid : public SceneObject
{
public:
	Pyramid(Mesh* mesh, float x, float y, float z);
	~Pyramid();
	void Draw();
	void Update();
	//void InitObjectsMaterials();
	//static bool Load(char* path);

private:

	static Vertex vertices[];
	static Color colors[];

	static Vertex* indexedVertices;
	static Color* indexedColors;
	static GLushort* indices;

	static int numVertices, numColors, numIndicies;
	GLfloat _rotation;
	Vector3 _position;
};


