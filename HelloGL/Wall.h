#pragma once
#include <Windows.h> // OpenGL for windows
#include <gl/GL.h> // OpenGL
#include <gl/GLU.h> // OpenGL Utilities
#include "GL/freeglut.h" //freeglut library
#include "Cube.h"
#include "SceneObject.h"
#include "Rectangle.h"

class Player;
#define PI 3.14159265

class Wall
{
public:
	Wall(float z);
	~Wall();
	void Draw();
	void GenerateWall();
	void Update();

	float _Zposition;

	bool WallCollision(Player* s1);

private:
	returnInts GetPos(int num1);

	Cube* wallArray[49];

	int numberOfTiles;

	float CalculateDistanceSquared(SceneObject* s1, SceneObject* s2);


};

