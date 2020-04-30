#include "Cube.h"
#include <iostream>

using namespace std;


Cube::Cube(Mesh* mesh,Texture2D* texture, float x, float y, float z) : SceneObject(mesh)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
	_rotation = -90.0f;
	_texture = texture;

	_width = (_mesh->Vertices[0].x - _mesh->Vertices[1].x) + (_mesh->Vertices[0].y - _mesh->Vertices[1].y) + (_mesh->Vertices[0].z - _mesh->Vertices[1].z);
	cout << _width << endl;

}

Cube::~Cube()
{

}

void Cube::Draw()
{

	glPushMatrix();
	glTranslatef(_position.x, _position.y, 0);
	glRotatef(_rotation, 0.0f, 0.0f, 1.0f);
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

void Cube::Update()
{
	//_rotation += 0.001f;
	//if (_rotation >= 360.0f)
	//{
	//	_rotation = 0.0f;
	//}

}

void Cube::SetRotation(float rotation)
{
	_rotation = rotation;
}

void Cube::SetUpMaterial()
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