#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "Point.h"
#include "Vector2D.h"


class Camera
{
public:
	static Camera* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera(); }
	void Update(float deltaTime);
	inline SDL_Rect GetCameraRect() { return cameraRect; }
	inline Vector2D GetPosition() { return m_Position; }
	//we want this to set the value of the target that the camera is on
	inline void SetTarget(Point* target) { m_Target = target; }


	~Camera();
private:
	Camera() { cameraRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }; }
	static Camera* s_Instance;
	SDL_Rect cameraRect;
	Point* m_Target;// the value we are going to be giving to this camera in our case is going to be the centre, the origin of our player
	//we'll make a calculation of the origin of our player and pass it to the camera
	Vector2D m_Position;// for the current position of the camera, our player will be calculated using this component
};




