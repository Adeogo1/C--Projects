#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "Commons.h"
#include "Transform.h"
#include "Point.h"





class GameObject
{
public:
	GameObject(Properties* props) : m_TextureID(props->TextureID), m_Width(props->Width), m_Height(props->Height), m_Flip(props->Flip) {
		m_Transform = new Transform(props->X, props->Y);	//we need to create a new instance of transform 
		// if we want to have the centre of an obj, we do the current position + the width and height divided by 2
		float px = props->X + props->Width / 2;
		float py = props->Y + props->Height / 2;
		m_Origin = new Point(px, py);
	}

	inline Point* GetOrigin() { return m_Origin; }

	virtual void Render(){}
	virtual void Update(float deltaTime){}
	virtual void Clean(){}
	~GameObject(){}

protected:
	Point* m_Origin;
	Transform* m_Transform;
	int m_Width, m_Height;
	string m_TextureID;
	SDL_RendererFlip m_Flip;
};
