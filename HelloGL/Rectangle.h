#pragma once
#include "SceneObject.h"
class Rectangle : public SceneObject
{
private:
	Material* _material;

public:
	Rectangle(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~Rectangle();

	void Draw();
	void Update();

	void SetUpMaterial();

	void SetRotation(float rotation);
};

