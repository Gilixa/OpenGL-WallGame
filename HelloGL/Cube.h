#pragma once
#include "SceneObject.h"
#include "Texture2D.h"
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"

class Cube : public SceneObject
{
private:
	Material* _material;

public:
	Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~Cube();

	void Draw();
	void Update();

	void SetUpMaterial();

	void SetRotation(float rotation);

};

