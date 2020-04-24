#include "Player.h"
#include <iostream>

using namespace std;


Player::Player(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
	_rotation = 0.0f;
	_texture = texture;

	_width = (_mesh->Vertices[0].x - _mesh->Vertices[1].x) + (_mesh->Vertices[0].y - _mesh->Vertices[1].y) + (_mesh->Vertices[0].z - _mesh->Vertices[1].z);

	alive = true;
	currentSpeed = PLAYER_SPEED;

}

Player::~Player()
{

}

void Player::Draw()
{
	glPushMatrix();

	glTranslatef(_position.x, _position.y, _position.z);
	glRotatef(_rotation, 0.0f, 0.0f, 1);



	glEnable(GL_NORMAL_ARRAY);
	glBindTexture(GL_TEXTURE_2D, _texture->GetID());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
	//glColorPointer(3, GL_FLOAT, 0, _mesh->Colors);
	glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);
	glNormalPointer(GL_FLOAT, 0, _mesh->Normals);
	SetUpMaterial();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, _mesh->Indices);
	glPopMatrix();
	//glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Player::Update()
{
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


void Player::Keyboard(unsigned char key, int x, int y)
{
	//switch (key)
	//{
	//case('d'):
	//	_position.x += 0.1f;
	//	break;
	//case('a'):
	//	_position.x -= 0.1f;
	//	break;

	//case('w'):
	//	_position.z += 0.1f;
	//	break;
	//case('s'):
	//	_position.z -= 0.1f;
	//	break;


	//default:
	//	break;
	//}


	//if (key == 'a')
	//{
	//	_position.x += 0.1f;
	//}

	//if (key == 'd')
	//{
	//	_position.x -= 0.1f;
	//}

	//if (key == 'w')
	//{
	//	_position.y += 0.1f;
	//}

	//if (key == 's')
	//{
	//	_position.y -= 0.1f;
	//}

}