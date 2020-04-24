#pragma once
#include <Windows.h> // OpenGL for windows
#include <gl/GL.h> // OpenGL
#include <gl/GLU.h> // OpenGL Utilities
#include "GL/freeglut.h" //freeglut library
#include "GLUTCallBacks.h"
#include "Structures.h"
#include "Cube.h"
#include "Pyramid.h"
#include "Player.h"
#include "SceneObject.h"
#include <vector>
#include "Wall.h"

#define REFRESHRATE 16
//The number of keyboard buttons checked
#define KEYBOARDCOUNT 7

#define CAMERA_MODIFIER 0.005f

#define NUMBEROFCUBES 0
#define NUMBEROFWALLSSPAWN 3
#define WALLSPAWNTIME 1.5
#define PI 3.14159265
#define WALLSEPARATION 200


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
	void KeyboardUp(unsigned char key, int x, int y);
	void MouseWheel(int wheel, int direction, int x, int y);
	void Mouse(int button, int state, int x, int y);
	void MouseMove(int x, int y);


	void InitObjects();
	void InitLighting();
	void InitGL(int argc, char* argv[]);
	void KeyboardUpdate();
	void CameraUpdate();
	void DrawString(const char* text, Vector3* position, Color* color);
	float CalculateDistanceSquared(SceneObject* s1, SceneObject* s2);



private:
	Camera* camera;

	Vector4* _lightPosition;
	Lighting* _lightData;

	Player* player;

	std::vector<Wall*> walls;


	bool keyboard[KEYBOARDCOUNT];
	int distanceFromPlayer;


	float deltaAngleX = 0.0f;
	int xOrigin = -1;
	float angleX = 0.0f;

	float deltaAngleY = 0.0f;
	int yOrigin = -1;
	float angleY = 0.0f;

	float x;

	bool rmbDown;	

	float wallSpawnTimer;
	int zWallSpawn;
	float score;

};

