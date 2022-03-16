#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"


const int TARGET_FPS = 60;
const float TARGET_DELTATIME = 1.5;


class Timer
{
public:
	void Tick();
	inline float GetDeltaTime() { return m_DeltaTime; }
	static Timer* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Timer(); }

	~Timer();

private:
	Timer();
	static Timer* s_Instance;
	float m_DeltaTime;// we need to also have the value of the last time because the delta time is the value that occurs between two event and for that we need to know the first time and the actual time 
	float m_LastTime;

};



