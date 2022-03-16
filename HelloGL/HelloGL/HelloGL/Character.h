#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"

#include "Objshapes.h"
#include "Structure.h"
#include "Texture2D.h"


class Character : public Objshapes
{
public:
	Character(Obj* obj, Texture2D* textrures, float x, float y, float z);
	void Update();
	void Keyboard(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void Draw();
	void ResetBallPosition();
	Vector3 GetPos() { return m_position; }
	inline void SetPos(Vector3 pos) { m_position = pos; }
	void AddGravity(float yPos, float depth);
	~Character();

private:
	int old_t;
	float dt;
	bool m_buttonPressed;
	Vector3 m_position;
	Vector3 m_Vrotation;
	float m_Rotation;
};



