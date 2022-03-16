#pragma once
#include "Structure.h"
#include "ObjLoader.h"




class Objshapes
{
public:
	Objshapes(Obj* obj, Texture2D* textrures, float x, float y, float z);
	virtual void Update();
	virtual void Keyboard(unsigned char key, int x, int y);
	virtual void KeyboardUp(unsigned char key, int x, int y);
	virtual void Draw();
	virtual void InitObjectsMaterials();	
	inline virtual void SetResetPos(float pos) { m_resetPos = pos; }
	inline virtual float GetResetPos() { return m_resetPos; }
	inline virtual void SetDistanceTravelled(float dis) { m_distanceTravelled = dis; }
	void AddGravity(float yPos, float depth) {}
	~Objshapes();

protected:
	Obj* _obj;
	Texture2D* _textrures;
	float m_distanceTravelled;
	float m_resetPos;
	


private:

};

