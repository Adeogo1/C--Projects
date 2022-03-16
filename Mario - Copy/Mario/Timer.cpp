#include "Timer.h"





Timer* Timer::s_Instance = nullptr;


Timer::Timer()
{
	m_DeltaTime = 0.0f;
	m_LastTime = 0.0f;
}

void Timer::Tick() {

	//get the value of the time since sdl was initialised
	m_DeltaTime = (SDL_GetTicks() - m_LastTime) * (TARGET_FPS / 1000.0f); //delta TIME IS THE DIFFERENCE OF TIME BETWEEN 2 EVENTS
	if (m_DeltaTime > TARGET_DELTATIME)
	{
		m_DeltaTime = 1.5f;
	}
	m_LastTime = SDL_GetTicks();
}


Timer::~Timer()
{
}