#pragma once
#include <Windows.h> // OpenGL for windows
#include <gl/GL.h> // OpenGL
#include <gl/GLU.h> // OpenGL Utilities
#include "GL/freeglut.h" //freeglut library
#include "GLUTCallBacks.h"
#include "Structures.h"
#include "Cube.h"
#include "Pyramid.h"

#define REFRESHRATE 16


class HelloGL
{
public:
	//Constructor
	HelloGL(int argc, char* argv[]);

	//Destructor
	~HelloGL(void);

	void Display();

	void Update();

	void Keyboard(unsigned char key, int x, int y);

	void InitObjects();
	void InitLighting();
	void InitGL(int argc, char* argv[]);

private:
	Camera* camera;
	SceneObject* objects[1000];
	Vector4* _lightPosition;
	Lighting* _lightData;

};

