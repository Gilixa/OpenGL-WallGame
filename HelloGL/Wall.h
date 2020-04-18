#pragma once
#include <Windows.h> // OpenGL for windows
#include <gl/GL.h> // OpenGL
#include <gl/GLU.h> // OpenGL Utilities
#include "GL/freeglut.h" //freeglut library
#include "Cube.h"

#define numberOfWallTiles 49

class Wall
{
public:
	Wall(float z);
	~Wall();

	void Draw();
	void GenerateWall();



private:
	int RollNumbers(int numberOfNumbers, int num1, int num2, int num3, int num4);
	float _Zposition;
	Cube* wallArray[numberOfWallTiles];

};

