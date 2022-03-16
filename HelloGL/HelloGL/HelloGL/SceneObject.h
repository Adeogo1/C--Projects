#pragma once
#include "Structure.h"
#include "Texture2D.h"

class SceneObject
{
public:
	SceneObject(Mesh* mesh, Texture2D* texture);
	virtual ~SceneObject();

	virtual void Update();
	virtual void Draw();

private:



protected:
	Mesh* _mesh;
	Obj* _obj;
	Texture2D* _texture;


};


