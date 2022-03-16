#pragma once
#include "Objshapes.h"
#include "Structure.h"



class ObjCube : public Objshapes
{
public:
	ObjCube(Obj* obj, Texture2D* textrures, float x, float y, float z);
	~ObjCube();
	void Draw();
	void Update();
	void Keyboard(unsigned char key, int x, int y);
	void InitObjectsMaterials();
	//inline void SetResetPos(float pos) { m_resetPos = pos; }
	//inline void SetDistanceTravelled(float dis) { m_distanceTravelled = dis; }

private:
	Vector3 m_position;
	float startPos;
	//float m_resetPos;
	float m_distanceTravelled;

	Material* _material;
};


