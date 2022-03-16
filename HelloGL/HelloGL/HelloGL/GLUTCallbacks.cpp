#include "GLUTCallbacks.h"
#include "HelloGL.h"

namespace GLUTCallbacks {
	namespace {
		HelloGL* helloGL = nullptr;
	}
	int updateTime = 0;
	void Init(HelloGL* gl) {
		helloGL = gl;


	}
	void Display() {
		if (helloGL != nullptr)
		{
			helloGL->Display();
		}
	}
	void Timer(int preferredRefresh) {
		updateTime = glutGet(GLUT_ELAPSED_TIME);
		helloGL->Update();
		updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
		glutTimerFunc(preferredRefresh - updateTime, GLUTCallbacks::Timer, preferredRefresh);
	}

	void Keyboard(unsigned char key, int x, int y) {
		helloGL->Keyboard(key, x, y);
	}

	void CreateMenu(int choice)
	{
		helloGL->CreateMenu(choice);
	}

	void KeyboardUp(unsigned char key, int x, int y) {
		helloGL->KeyboardUp(key, x, y);
	}

	void Special(int key, int x, int y) {
		helloGL->Special(key, x, y);
	}
	void SpecialUp(int key, int x, int y) {
		helloGL->SpecialUp(key, x, y);
	}
	void Mouse(int button, int state, int x, int y) {
		helloGL->Mouse(button, state, x, y);
	}

	void Motion(int x, int y) {
		helloGL->Motion( x, y);
	}
	void PassiveMotion(int x, int y) {
		helloGL->PassiveMotion( x, y);
	}

}