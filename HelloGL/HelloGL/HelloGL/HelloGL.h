#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "GLUTCallbacks.h"
#include "MeshLoader.h"
#include "ObjCube.h"
#include "ObjBarrels.h"
#include "ObjShapes.h"
#include "Character.h"
#include <fstream>
#include <math.h>
#include <ctime>
#include <cstdlib>
using namespace GLUTCallbacks;
#define REFRESHRATE 16

class HelloGL
{
public:
	HelloGL(int argc, char* argv[]);
	~HelloGL(void);
	void Display();
	void Update();
	void InitObjects();
	void InitGL(int argc, char* argv[]);
	void InitObjectsLightObject();
	void InitObjLoaders();
	void UpdateObjs();
	void DrawObjs();
	float calculateDistanceSquared(Vector3 p1, Vector3 p2);
	void Reset();
	void CreateMenu(int choice);

	
	void Keyboard(unsigned char key, int x, int y);
	void Menu();
	void KeyboardUp(unsigned char key, int x, int y);
	void Special(int key, int x, int y);//For special keys, such as the function keys. Accessed by glut enums. E.g. GLUT_KEY_F1
	void SpecialUp(int key, int x, int y);//Called when a special key is released
	void Mouse(int button, int state, int x, int y);//triggers when mouse buttons are pressed
	void Motion(int x, int y);//Called when the mouse moves whilst a button is pressed
	void PassiveMotion(int x, int y);//called when the mouse moves without any buttons being pressed
	void DrawString(const char* text, Vector3* position, Color* color);


	//void DrawPolygon();
	//void DrawPolygon2();
	//void DrawPolygon3D();
	//void DrawRectangle(float width, float height);
	////void DrawCircle(float radius, int numSides /* = 8 */);
	//void DrawCube();
	//void DrawCubeArray();
	//void DrawIndexedCube();
	//void DrawCubeArrayAlt();
	//void DrawIndexedCubeArrayAlt();


private:
	int old_t;
	float rotation;
	Vector3 position;
	float M_PI = 3.14;
	Camera* camera;
	SceneObject* objects[1000];
	Objshapes* m_SkyBox;
	
	ObjBarrels* m_objects[8];
	Character* m_Player;
	Objshapes* m_Platform[2];

	Vector3 m_ObjPositions;
	Vector3 startPos;

	bool m_Alive;

	//static Vertex vertices[];
	//static Color colors[];

	static Vertex indexedVertices[];
	static Color indexedColors[];
	static GLushort indices[];

	Vector4* _lightPosition;
	Lighting* _lightData;
	
	int framecount, distance;

	float playerRadius, boxRadius;

	ifstream infile;
	ofstream outfile;
	int highestScore = 0;
	int fileHighScore;
};




