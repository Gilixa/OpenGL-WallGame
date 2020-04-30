#pragma once
#include "SceneObject.h"

class Rect : public SceneObject
{
private:
	Material* _material;

public:
	Rect(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~Rect();

	void Draw();
	void Update();

	void SetUpMaterial();

	void SetRotation(float rotation);
	float _width;
};

