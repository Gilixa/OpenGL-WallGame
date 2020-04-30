#include "HelloGL.h"
#include "MeshLoader.h"
#include "Texture2D.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include <sstream>

using namespace std;

HelloGL::HelloGL(int argc, char* argv[])
{
	srand(time(NULL));
	
	
	InitGL(argc, argv);
	InitObjects();
	//InitLighting();
	glutMainLoop();


}

void HelloGL::InitObjects()
{
	camera = new Camera();
	camera->eye.x = 0.0f; camera->eye.y = 2.0f; camera->eye.z = -20.0f;
	//camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;

//	Mesh* pyramidMesh = MeshLoader::Load((char*)"pyramid.txt");


	player = new Player(0, 0, 0);
	walls.push_back(new Wall(player->_position.z + WALLSEPARATION));
	wallSpawnTime = WALLSPAWNTIME;
	distanceFromPlayer = 10;
	rmbDown = false;
	x = 0;
	_paused = false;;
	
}

void HelloGL::InitGL(int argc, char* argv[])
{

	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Simple OpenGL Program");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutKeyboardUpFunc(GLUTCallbacks::KeyboardUp);
	glutMouseWheelFunc(GLUTCallbacks::MouseWheel);
	glutMouseFunc(GLUTCallbacks::Mouse);
	glutMotionFunc(GLUTCallbacks::MouseMove);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Set the viewport to be the entire window*/-
	glViewport(0, 0, 800, 800);
	//Set the correct perspective
	gluPerspective(45, 1, 0.1, 1000);
	glEnable(GL_TEXTURE_2D); 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	glCullFace(GL_BACK);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	
	glMatrixMode(GL_MODELVIEW);
}

void HelloGL::InitLighting()
{
	_lightPosition = new Vector4();
	_lightPosition->x = 0.0;
	_lightPosition->y = 1.0;
	_lightPosition->z = 0.0;

	_lightData = new Lighting();
	_lightData->Ambient.x = 0.2;
	_lightData->Ambient.y = 0.2;
	_lightData->Ambient.z = 0.2;
	_lightData->Ambient.w = 1.0;
	_lightData->Diffuse.x = 0.8;
	_lightData->Diffuse.y = 0.8;
	_lightData->Diffuse.z = 0.8;
	_lightData->Diffuse.w = 1.0;
	_lightData->Specular.x = 0.2;
	_lightData->Specular.y = 0.2;
	_lightData->Specular.z = 0.2;
	_lightData->Specular.w = 1.0;

}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the scene
	player->Draw();


	if (player->alive)
	{


		for (int i = 0; i < walls.size(); i++)
		{
			walls[i]->Draw();
		}

	}
	else
	{
		Vector3 v = { player->_position.x + 1.0f,player->_position.y + 3.0f, player->_position.z + 5.0f };
		Color c = { 0.0f,1.0f,0.0f };
		DrawString("You died \n Press R to restart", &v, &c);

	}
	
	int postScore = score;
	stringstream ss;
	ss << "Score: " << postScore;
	string textString = ss.str();
	const char* text = textString.c_str();

	Vector3 v = { player->_position.x + 5.0f,player->_position.y + 2.0f,player->_position.z + 5.0f };
	Color c = { 0.0f,1.0f,0.0f };

	DrawString(text, &v, &c);

	glFlush();
	glutSwapBuffers();
}

HelloGL::~HelloGL(void)
{
	delete camera;
	camera = NULL;

	delete player;
	player = NULL;

	walls.clear();

}

void HelloGL::Update()
{
	KeyboardUpdate();
	CameraUpdate();

	glLoadIdentity();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	glutPostRedisplay();

	if (player->alive && !_paused)
	{
		//glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
		//glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Diffuse.x));
		//glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->Specular.x));
		//glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));

		//Generate a new wall

		if (wallSpawnTimer > wallSpawnTime)
		{
			walls.push_back(new Wall(player->_position.z + WALLSEPARATION));
			wallSpawnTimer = 0;
		}
		else
		{
			wallSpawnTimer += 0.01f;
		}

		for (int i = 0; i < walls.size(); i++)
		{
			walls[i]->Update();

			if (walls[i]->_Zposition < player->_position.z - 20)
			{
				score += 1;
				player->currentSpeed += 0.05;
				wallSpawnTime -= 0.002;
				walls.erase(walls.begin() + i);
			}

		}
		player->Update();

		if (walls.size() > 0)
		{
			//Only need to check 1st wall in the vector as every old wall is deleted
			if (walls[0]->WallCollision(player))
			{
				player->alive = false;
				player->_position = { 0,0,0 };
				player->currentSpeed = PLAYER_SPEED;
				angleX = 0;
				angleY = 0;
				distanceFromPlayer = 10;
				camera->eye.x = player->_position.x + sin(angleX + deltaAngleX) * cos(angleY + deltaAngleY) * distanceFromPlayer;
				camera->eye.y = player->_position.y + sin(angleY + deltaAngleY) * distanceFromPlayer;
				camera->eye.z = player->_position.z - cos(angleX + deltaAngleX) * cos(angleY + deltaAngleY) * distanceFromPlayer;
			}
		}
	}
}

//-----------------------------------------------------
//Keyboard settings
//-----------------------------------------------------
//0-A 
//1-S 
//2-D
//3-W
//4-Q
//5-E
//6-R
//7-P

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case('a'):
		keyboard[0] = true;
		break;
	case('s'):
		keyboard[1] = true;
		break;
	case('d'):
		keyboard[2] = true;
		break;
	case('w'):
		keyboard[3] = true;
		break;
	case('q'):
		keyboard[4] = true;
		break;
	case('e'):
		keyboard[5] = true;
		break;
	case('r'):
		keyboard[6] = true;
		break;
	case('p'):
		if (_paused)
			_paused = false;
		else
			_paused = true;
	default:
		break;

	}
}

void HelloGL::KeyboardUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	case('a'):
		keyboard[0] = false;
		break;
	case('s'):
		keyboard[1] = false;
		break;
	case('d'):
		keyboard[2] = false;
		break;
	case('w'):
		keyboard[3] = false;
		break;
	case('q'):
		keyboard[4] = false;
		break;
	case('e'):
		keyboard[5] = false;
		break;
	case('r'):
		keyboard[6] = false;
		break;
	default:
		break;
	}
}

void HelloGL::KeyboardUpdate()
{
	if (keyboard[3])
	{
		//player->_position.y += PLAYER_SPEED * cos(player->_rotation * PI/180);
		//player->_position.x -= PLAYER_SPEED * sin(player->_rotation * PI / 180);

		if (player->_position.y + PLAYER_SPEED / 2 < 7)
			player->_position.y += PLAYER_SPEED / 2;
		 
	}

	if (keyboard[1])
	{
		if (player->_position.y + PLAYER_SPEED / 2 > -7)
			player->_position.y -= PLAYER_SPEED / 2;
		//player->_position.y -= PLAYER_SPEED * cos(player->_rotation * PI / 180);
		//player->_position.x += PLAYER_SPEED * sin(player->_rotation * PI / 180);

	}

	if (keyboard[0])
	{
		if (player->_position.x + PLAYER_SPEED / 2 < 7)
			player->_position.x += PLAYER_SPEED / 2;

		//player->_position.x += PLAYER_SPEED * cos(player->_rotation * PI / 180);
		//player->_position.y += PLAYER_SPEED * sin(player->_rotation * PI / 180);

	}

	if (keyboard[2])
	{
		if (player->_position.x - PLAYER_SPEED / 2 > -7)
			player->_position.x -= PLAYER_SPEED / 2;
		//player->_position.x -= PLAYER_SPEED * cos(player->_rotation * PI / 180);
		//player->_position.y -= PLAYER_SPEED * sin(player->_rotation * PI / 180);
	
	}

	if (keyboard[4])
	{
		player->_rotation -= 3;
	}

	if (keyboard[5])
	{
		player->_rotation += 3;
	}

	if (keyboard[6])
	{
		player->alive = true;
		player->_position = { 0,0,0 };
		player->_rotation = 0;
		angleX = 0;
		angleY = 0;
		score = 0;
		distanceFromPlayer = 10;
		wallSpawnTime = WALLSPAWNTIME;
		wallSpawnTimer = 0;
		camera->eye.x = player->_position.x + sin(angleX + deltaAngleX) * cos(angleY + deltaAngleY) * distanceFromPlayer;
		camera->eye.y = player->_position.y + sin(angleY + deltaAngleY) * distanceFromPlayer;
		camera->eye.z = player->_position.z - cos(angleX + deltaAngleX) * cos(angleY + deltaAngleY) * distanceFromPlayer;
		walls.clear();
		walls.push_back(new Wall(player->_position.z + WALLSEPARATION));
	}
}

void HelloGL::CameraUpdate()
{

	////eye.x = Object.X + cos(someangle)*(distance from object)
	camera->eye.x = player->_position.x + sin(angleX + deltaAngleX) * cos(angleY + deltaAngleY) * distanceFromPlayer;
	camera->eye.y = player->_position.y + sin(angleY + deltaAngleY) * distanceFromPlayer;
	camera->eye.z = player->_position.z - cos(angleX + deltaAngleX) * cos(angleY + deltaAngleY) * distanceFromPlayer;

	camera->center.x = player->_position.x;
	camera->center.y = player->_position.y;
	camera->center.z = player->_position.z;


}

void HelloGL::MouseWheel(int wheel, int direction, int x, int y)
{
	switch (direction)
	{
	case(1):
		distanceFromPlayer -= 1;
		break;
	case(-1):
		distanceFromPlayer += 1;
		break;
	default:
		break;
	}
}

void HelloGL::Mouse(int button, int state, int x, int y)
{

	switch (button)
	{
	case(GLUT_LEFT_BUTTON):
		if (state == GLUT_UP)
		{
			yOrigin = -1;
			xOrigin = -1;
			
			angleY += deltaAngleY;
			angleX += deltaAngleX;

			deltaAngleX = 0;
			deltaAngleY = 0;

		}
		else
		{
			xOrigin = x;
			yOrigin = y;
		}
	
	
	}

}

void HelloGL::MouseMove(int x, int y)
{
	if (xOrigin >= 0)
	{
		deltaAngleX = (x - xOrigin) * CAMERA_MODIFIER;
		deltaAngleY = (y - yOrigin) * CAMERA_MODIFIER;
	}
}

float HelloGL::CalculateDistanceSquared(SceneObject* s1, SceneObject* s2)
{
	float distance = ((s1->_position.x - s2->_position.x) * (s1->_position.x - s2->_position.x)) + ((s1->_position.y - s2->_position.y) * (s1->_position.y - s2->_position.y)) + ((s1->_position.z - s2->_position.z) * (s1->_position.z - s2->_position.z));

	return distance;
}

void HelloGL::DrawString(const char* text, Vector3* position, Color* color)
{
	glColor3f(color->r, color->g, color->b);
	glTranslatef(position->x, position->y, position->z);
	glRasterPos2f(0,0);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(unsigned char*)text);

	glColor3f(1, 1, 1);
}

