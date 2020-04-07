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
	InitLighting();
	glutMainLoop();


}

void HelloGL::InitObjects()
{
	camera = new Camera();
	camera->eye.x = 5.0f; camera->eye.y = 5.0f; camera->eye.z = -5.0f;
	//camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;


	Mesh* cubeMesh = MeshLoader::Load((char*)"Cube.txt");
	//Mesh* pyramidMesh = MeshLoader::Load((char*)"pyramid.txt");
	Texture2D* texture = new Texture2D();
	texture->Load((char*)"penguins.raw", 512, 512);
	
	objects[0] = new Cube(cubeMesh, texture, 0, 0,0);

	for (int i = 1; i < 500; i++)
	{
		objects[i] = new Cube(cubeMesh,texture, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand()%1000)/10.0f);
	}
	
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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Set the viewport to be the entire window
	glViewport(0, 0, 800, 800);
	//Set the correct perspective
	gluPerspective(45, 1, 0.1, 1000);
	glEnable(GL_TEXTURE_2D); 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	glCullFace(GL_BACK);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	
	
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

	
	for (int i = 0; i < 500; i++)
	{
		objects[i]->Draw();
	}
	
	glFlush(); // flushes the scene drawn to the graphics card
	glutSwapBuffers();
}


HelloGL::~HelloGL(void)
{
	delete camera;
	camera = NULL;
	for (int i = 0; i < 500; i++)
	{
		delete objects[i];
		objects[i] = NULL;
	}
}

void HelloGL::Update()
{

	glLoadIdentity();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	glutPostRedisplay();
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->Specular.x));

	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));


	for (int i = 0; i < 500; i++)
	{
		objects[i]->Update();
	}
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case('d'):
		camera->eye.x += 0.1f;
		break;
	case('a'):
		camera->eye.x -= 0.1f;
		break;

	case('w'):
		camera->eye.z += 0.1f;
		break;
	case('s'):
		camera->eye.z -= 0.1f;
		break;


	default:
		break;
	}
}
