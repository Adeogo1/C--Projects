#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;



struct Vector2
{
	float x;
	float y;
};

struct Vector3
{
	float x;
	float y;
	float z;
};

struct Vector4
{
	float x;
	float y;
	float z;
	float w;
};

struct Lighting
{
	Vector4 Ambient;
	Vector4 Diffuse;
	Vector4 Specular;
};

struct Material
{
	Vector4 Ambient;
	Vector4 Diffuse;
	Vector4 Specular;
	GLfloat Shininess;
};

struct Camera
{
	Vector3 eye;
	Vector3 center;
	Vector3 up;
};

struct Color
{
	GLfloat r, g, b;
};
struct Vertex
{
	GLfloat x, y, z;
};



struct TexCoord
{
	GLfloat u;
	GLfloat v;
};


//struct Mesh
//{
//	Vertex* Vertices;
//	Color* Colors;
//	GLushort* Indices;
//	TexCoord* TexCoord;
//	int VertexCount, ColorCount, IndexCount, TexCoordCount;
//
//};

struct Mesh
{
	Vertex* Vertices;
	Vector3* Normals;
	GLushort* Indices;
	TexCoord* TexCoord;
	int VertexCount, NormalCount, IndexCount, TexCoordCount;
};

struct Obj
{
	vector<Vector3> vertex;
	vector<Vector2> TexCoord;
	vector<Vector3> Normals;
	vector<GLushort> Vertices;
	vector<GLushort> Normalindicies;
	vector<GLushort> TexCoordsindices;
	int Indicies;
};


enum Axis {
	HORIZONTAL,
	VERTICAL
};

struct Sphere
{
	float radius;
	Vector3 position;
};

struct BoxCollider2D
{
public:
	BoxCollider2D(Vector3 origin, float width, float height) {
		Origin = origin;
		Width = Origin.x + width;
		Height = Origin.y + height;
	}

public:
	Vector3 Origin;
	float Width, Height;
	
};

struct BoxCollider3D
{

	Vector3 Origin;
	float Width, Height, Depth;
	
	BoxCollider3D(Vector3 origin, float width, float height, float depth) {
		Origin = origin;
		Width = Origin.x + width;
		Depth = Origin.y + height;
		Height = Origin.z + depth;
	}
};
