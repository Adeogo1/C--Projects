#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "GLUTCallbacks.h"
#include "SceneObject.h"
#include <iostream>
#include <fstream>
using namespace std;



class Cube : public SceneObject
{
public:
	Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~Cube();

	void Draw();
	void Update();
	void SetRotation(float rotation);
	void InitObjectsMaterials();
	//static bool Load(char* path);

private:

	//static Vertex vertices[];
	//static Color colors[];

	//static Vertex* indexedVertices;
	//static Color* indexedColors;
	//static GLushort* indices;

	//static int numVertices, numColors, numIndicies;
	GLfloat _rotation;
	Vector3 _position;
	float randRot;
	float startPos;

	Material* _material;

};


