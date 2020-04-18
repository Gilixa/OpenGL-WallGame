#pragma once

#include "Structures.h"
#include "Texture2D.h"
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"


class SceneObject
{
protected:
	Mesh* _mesh;
	Texture2D* _texture;
	float _width;





public:
	SceneObject(Mesh* mesh, Texture2D* texture);
	virtual ~SceneObject();

	virtual void Update();
	virtual void Draw();
	virtual float GetWidth();

	

	GLfloat _rotation;
	Vector3 _position;
};

