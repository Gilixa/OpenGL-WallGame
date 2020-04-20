#pragma once
#include <Windows.h> // OpenGL for windows
#include <gl/GL.h> // OpenGL
#include <gl/GLU.h> // OpenGL Utilities
#include "GL/freeglut.h" //freeglut library
#include "Cube.h"


class Wall
{
public:
	Wall(float z);
	~Wall();

	void Draw();
	void GenerateWall();
	void Update();

	float _Zposition;

private:
	returnInts RollNumbers(int numberOfNumbers, int num1, int num2, int num3, int num4);
	returnInts RollNumbers(int num1);
	returnInts GetPos(int num1);

	Cube* wallArray[49];

	int numberOfTiles;

};

