#pragma once
#include "SceneObject.h"
#include "Texture2D.h"
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"

class Pyramid : public SceneObject
{
public:
	Pyramid(Mesh* mesh, float x, float y, float z);
	~Pyramid();

	void Draw();
	void Update();

	void SetRotation(float rotation);
	GLfloat _rotation;
	Vector3 _position;
};

