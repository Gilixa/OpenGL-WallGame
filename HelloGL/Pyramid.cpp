#include "Pyramid.h"
Pyramid::Pyramid(Mesh* mesh, float x, float y, float z) : SceneObject(mesh, nullptr)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
	_rotation = 0.0f;

}

Pyramid::~Pyramid()
{

}

void Pyramid::Draw()
{


	//glRotatef(_rotation, 1.0f, 0.0f, 0.0f);
	glTranslatef(_position.x, _position.y, _position.z);

	//glBindTexture(GL_TEXTURE_2D, _texture->GetID());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
	//glColorPointer(3, GL_FLOAT, 0, _mesh->Colors);
	//glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);
	glPushMatrix();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, _mesh->Indices);

	glPopMatrix();
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Pyramid::Update()
{
	_rotation += 0.001f;
	if (_rotation >= 360.0f)
	{
		_rotation = 0.0f;
	}
}

void Pyramid::SetRotation(float rotation)
{

}