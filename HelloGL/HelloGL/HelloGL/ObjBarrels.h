#pragma once
#include "Objshapes.h"



class ObjBarrels :
	public Objshapes
{
public:
	ObjBarrels(Obj* obj, Texture2D* textrures, float x, float y, float z);
	~ObjBarrels();
	void Draw();
	void Update();
	inline void SetResetPos(float pos) { m_resetPos = pos; }
	inline Vector3 GetPos() { return _position; }
	inline void SetPos(Vector3 pos) { _position = pos; }
	inline void SetDistanceTravelled(float dis) { m_distanceTravelled = dis; }


private:
	Vector3 _position;
	float startPos;
	float m_resetPos;
	float m_distanceTravelled;
};

