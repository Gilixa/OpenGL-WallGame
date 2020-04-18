#pragma once
class HelloGL;

namespace GLUTCallbacks
{
	void Init(HelloGL* gl);

	void Display();

	void Timer(int preferredRefresh);

	void Keyboard(unsigned char key, int x, int y);

	void KeyboardUp(unsigned char key, int x, int y);

	void MouseWheel(int wheel, int direction, int x, int y);

	void Mouse(int button, int state, int x, int y);

	void MouseMove(int x, int y);
}