#include "Player.h"
#include <iostream>
#include "MeshLoader.h"
#include "Rectangle.h"

using namespace std;


Player::Player(float x, float y, float z)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
	_rotation = 0.0f;

	alive = true;
	currentSpeed = PLAYER_SPEED;
	
	_texture = new Texture2D();
	_texture->LoadTextureTGA("test.tga");

	_mesh = MeshLoader::Load((char*)"Objects/Rectangle.txt");
	
	for (int i = 0; i < 2; i++)
	{
		playerArray[i] = new Rect(_mesh, _texture, i * 0.5, i, 0);
	}

	playerArray[0]->SetRotation(90);
}


Player::~Player()
{

}

void Player::Draw()
{


	glPushMatrix();
	glTranslatef(_position.x, _position.y, _position.z);
	glRotatef(_rotation, 0.0f, 0.0f, 1);

	for (int i = 0; i < 2; i++)
	{
		playerArray[i]->Draw();
	}

	glPopMatrix();

}

void Player::Update()
{
	for (int i = 0; i < 2; i++)
	{
		playerArray[i]->_position.z += currentSpeed;
	}

	_position.z += currentSpeed;
}

void Player::SetRotation(float rotation)
{

}

void Player::SetUpMaterial()
{
	_material = new Material();
	_material->Ambient.x = 0.8; _material->Ambient.y = 0.05; _material->Ambient.z = 0.05; _material->Ambient.w = 1.0;
	_material->Diffuse.x = 0.8; _material->Diffuse.y = 0.05; _material->Diffuse.z = 0.05; _material->Diffuse.w = 1.0;
	_material->Specular.x = 1.0; _material->Specular.y = 1.0; _material->Specular.z = 1.0; _material->Specular.w = 1.0;
	_material->Shininess = 100.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->Diffuse.x));
	glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->Specular.x));
	glMaterialf(GL_FRONT, GL_SHININESS, _material->Shininess);		
}

Vector3 Player::GetPosition()
{
	return _position;
}

void Player::SetPosition(Vector3 position)
{
	_position = position;
}
