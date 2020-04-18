#include "GLUTCallBacks.h"
#include "HelloGL.h"

//Namespace implimentation
namespace GLUTCallbacks
{
	namespace
	{
		//Initialize to a null pointer before anything is done
		HelloGL* helloGL = nullptr;
	}

	void Init(HelloGL* gl)
	{
		helloGL = gl;
	}

	void Display()
	{

		if (helloGL != nullptr)
		{
			helloGL->Display();
		}
	}


	void Timer(int preferredRefresh)
	{
		int updateTime = glutGet(GLUT_ELAPSED_TIME);
		helloGL->Update();
		updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
		glutTimerFunc(preferredRefresh - updateTime, GLUTCallbacks::Timer, preferredRefresh);


	}

	void Keyboard(unsigned char key, int x, int y)
	{
		helloGL->Keyboard(key, x, y);
	}


	void KeyboardUp(unsigned char key, int x, int y)
	{
		helloGL->KeyboardUp(key, x, y);
	}

	void MouseWheel(int wheel, int direction, int x, int y)
	{
		helloGL->MouseWheel(wheel,direction, x, y);
	}


	void Mouse(int button, int state, int x, int y)
	{
		helloGL->Mouse(button, state, x, y);
	}

	void MouseMove(int x, int y)
	{
		helloGL->MouseMove(x, y);
	}

}