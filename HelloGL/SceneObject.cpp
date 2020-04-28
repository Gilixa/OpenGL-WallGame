#include "SceneObject.h"

SceneObject::SceneObject(Mesh* mesh)
{
	_mesh = mesh;

}

SceneObject::~SceneObject()
{

}

void SceneObject::Draw()
{

}

void SceneObject::Update()
{

}

float SceneObject::GetWidth()
{
	return _width;
}