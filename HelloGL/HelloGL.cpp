#include "HelloGL.h"
#include "MeshLoader.h"
#include "Texture2D.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>




using namespace std;
HelloGL::HelloGL(int argc, char* argv[])
{
	srand(time(NULL));
	
	
	InitGL(argc, argv);
	InitObjects();
//	InitLighting();
	glutMainLoop();


}

void HelloGL::InitObjects()
{
	camera = new Camera();
	camera->eye.x = 0.0f; camera->eye.y = 2.0f; camera->eye.z = -20.0f;
	//camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;


	Mesh* cubeMesh = MeshLoader::Load((char*)"Cube.txt");
//	Mesh* pyramidMesh = MeshLoader::Load((char*)"pyramid.txt");
	Mesh* playerMesh = MeshLoader::Load((char*)"Cube.txt");
	Texture2D* texture = new Texture2D();
	Texture2D* texture2 = new Texture2D();
	texture->Load((char*)"penguins.raw", 512, 512);
	texture2->Load((char*)"stars.raw", 512, 512);
	
	//objects.push_back(new Cube(cubeMesh, texture, 0, 0, 0));

	player = new Player(playerMesh, texture2, 0, 0, 0);

	walls.push_back(new Wall(player->_position.z + WALLSEPARATION));


	for (int i = 0; i < NUMBEROFCUBES; i++)
	{
		objects.push_back(new Cube(cubeMesh, texture, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 100.0f));
	}

	distanceFromPlayer = 10;
	rmbDown = false;
	x = 0;

	//for (int i = 500; i < 1000; i++)
	//{
	//	objects[i] = new Pyramid(pyramidMesh, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 100.0f);
	//}
	
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




	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Draw();
	}

	player->Draw();

	for (int i = 0; i < walls.size(); i++)
	{
		walls[i]->Draw();
	}


	Vector3 v = { -1.4f,0.7f, -1.0f };
	Color c = { 0.0f,1.0f,0.0f };
	//DrawString("test", &v, &c);
	
	glFlush(); // flushes the scene drawn to the graphics card
	glutSwapBuffers();
}


HelloGL::~HelloGL(void)
{
	delete camera;
	camera = NULL;
	//for (int i = 0; i < 500; i++)
	//{
	//	delete objects[i];
	//	objects[i] = NULL;
	//}

	delete player;
	player = NULL;

	delete objects[0];
	objects[0] = NULL;

}

void HelloGL::Update()
{
	KeyboardUpdate();
	CameraUpdate();

	glLoadIdentity();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	glutPostRedisplay();


	//glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Diffuse.x));
	//glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->Specular.x));
	//glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));

	//Generate a new wall

	if (wallSpawnTimer > WALLSPAWNTIME)
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
			walls.erase(walls.begin() + i);

	}




	player->Update();




	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update();


		float distance = CalculateDistanceSquared(player, objects[i]);
		float widthDistance = player->GetWidth() + objects[i]->GetWidth();

		if (distance <= widthDistance)
		{
			cout << "collision" << endl;
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
	default:
		break;
	}
}

void HelloGL::KeyboardUpdate()
{


	if (keyboard[3])
	{


		player->_position.y += PLAYER_SPEED * cos(player->_rotation * PI/180);
		player->_position.x -= PLAYER_SPEED * sin(player->_rotation * PI / 180);

	}

	if (keyboard[1])
	{
		player->_position.y -= PLAYER_SPEED * cos(player->_rotation * PI / 180);
		player->_position.x += PLAYER_SPEED * sin(player->_rotation * PI / 180);

	}

	if (keyboard[0])
	{
		player->_position.x += PLAYER_SPEED * cos(player->_rotation * PI / 180);
		player->_position.y += PLAYER_SPEED * sin(player->_rotation * PI / 180);

	}

	if (keyboard[2])
	{
		player->_position.x -= PLAYER_SPEED * cos(player->_rotation * PI / 180);
		player->_position.y -= PLAYER_SPEED * sin(player->_rotation * PI / 180);
	
	}

	if (keyboard[4])
	{
		player->_rotation -= PLAYER_SPEED * 5;
	}

	if (keyboard[5])
	{
		player->_rotation += PLAYER_SPEED * 5;
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
	glTranslatef(position->x, position->y, position->z);
	glRasterPos2f(5.0f, 5.0f);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(unsigned char*)text);
}



//Wall could be its own object - making it easier to make more?

//void HelloGL::GenerateWall()
//{
//	int wallArray[9] = { 0 };
//
//	int numberGenerator = rand() % 9;
//	int secondNumber;
//
//	switch (numberGenerator)
//	{
//	case 0:
//		secondNumber = RollNumbers(2, 1, 3, NULL, NULL);
//		break;
//	case 1:
//		secondNumber = RollNumbers(3, 0, 2, 4, NULL);
//		break;
//	case 2:
//		secondNumber = RollNumbers(2, 1, 5, NULL, NULL);
//		break;
//	case 3:
//		secondNumber = RollNumbers(3, 0, 4, 6, NULL);
//		break;
//	case 4:
//		secondNumber = RollNumbers(4, 1, 3, 5, 7);
//		break;
//	case 5:
//		secondNumber = RollNumbers(3, 2, 4, 8, NULL);
//		break;
//	case 6:
//		secondNumber = RollNumbers(2, 3, 7, NULL, NULL);
//		break;
//	case 7:
//		secondNumber = RollNumbers(3, 4, 6, 8, NULL);
//		break;
//	case 8:
//		secondNumber = RollNumbers(2, 5, 7, NULL, NULL);
//		break;
//	}
//
//	wallArray[numberGenerator] = 1;
//	wallArray[secondNumber] = 1;
//
//}
//
//int HelloGL::RollNumbers(int numberOfNumbers, int num1, int num2, int num3, int num4)
//{
//	int numberGenerator = rand() % numberOfNumbers + 1;
//
//	switch (numberGenerator)
//	{
//	case 1:
//		return num1;
//		break;
//	case 2:
//		return num2;
//		break;
//	case 3:
//		return num3;
//		break;
//	case 4:
//		return num4;
//		break;
//	default:
//		return num1;
//		cout << "Please enter the correct numberOfNumbers" << endl;
//		break;
//	}
//}