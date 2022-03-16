#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "Commons.h"
#include "Engine.h"

class Input
{
public:
	static Input* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Input(); }
	void Listen(); //listen to events
	bool GetKeyDown(SDL_Scancode key);
	void KeyUp();
	int GetAxisKey(Axis axis);
	~Input();


private:
	Input() {
		m_KeyStates = SDL_GetKeyboardState(nullptr);
	}
	
	void KeyDown();

	const Uint8* m_KeyStates;//this array stores the state of your keyboard, when a button is pushed at the place in the array where that button has to be stored, the value one should be there. If one then a button was pushed

	static Input* s_Instance;
};