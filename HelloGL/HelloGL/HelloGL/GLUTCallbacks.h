#pragma once
class HelloGL;

namespace GLUTCallbacks {
	void Init(HelloGL* gl);

	void Display();

	void Timer(int preferredRefresh);

	void Keyboard(unsigned char key, int x, int y);

	void CreateMenu(int choice);
	
	void KeyboardUp(unsigned char key, int x, int y);

	void Special(int key, int x, int y);

	void SpecialUp(int key, int x, int y);

	void Mouse(int button, int state, int x, int y);

	void Motion(int x, int y);

	void PassiveMotion(int x, int y);
}

