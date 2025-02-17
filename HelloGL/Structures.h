#pragma once

#include <Windows.h>
#include <gl\GL.h>

struct Vector3
{
	float x;
	float y;
	float z;
};

struct Camera
{
	Vector3 eye;
	Vector3 center;
	Vector3 up;
};

struct Color
{
	GLfloat r, g, b;
};

struct Vertex
{
	GLfloat x, y, z;
};

struct TexCoord
{
	GLfloat u, v;
};

struct Mesh
{
	Vertex* Vertices;
	//Color* Colors;
	Vector3* Normals;
	GLushort* Indices;
	int VertexCount, ColorCount, IndexCount,TexCoordCount, NormalCount;
	TexCoord* TexCoords;
};

struct TexturedMesh
{
	Mesh* Mesh;
};


struct Vector4
{
	float x;
	float y;
	float z;
	float w;
};

struct Lighting
{
	Vector4 Ambient, Diffuse, Specular;
};

struct Material
{
	Vector4 Ambient, Diffuse, Specular;
	GLfloat Shininess;
};

struct returnInts
{
	int num1;
	int num2;
};