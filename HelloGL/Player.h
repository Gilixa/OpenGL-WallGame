#pragma once

#include "Texture2D.h"
#include "Structures.h"
#include "Cube.h"
#include "Rectangle.h"

#define PLAYER_SPEED 0.50f

class Player
{
private:
	Material* _material;
	Mesh* _mesh;
	Texture2D* _texture;


public:
	Player(float x, float y, float z);
	~Player();

	void Draw();
	void Update();
	void SetUpMaterial();
	void SetRotation(float rotation);
	Vector3 GetPosition();
	void SetPosition(Vector3 position);
	bool alive;
	float currentSpeed;

	GLfloat _rotation;
	Vector3 _position;
	float _width;

	Rect* playerArray[2];


};

