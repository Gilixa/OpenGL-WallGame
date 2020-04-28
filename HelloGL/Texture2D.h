#pragma once
#include <Windows.h> // OpenGL for windows
#include <gl/GL.h> // OpenGL
#include <gl/GLU.h> // OpenGL Utilities
#include "GL/freeglut.h" //freeglut library


class Texture2D
{
private:

	int _width, _height;

	GLuint _ID; // Texture ID
public:
	Texture2D();
	~Texture2D();

	bool Load(char* path, int width, int height);
	GLuint GetID() const { return _ID; }
	int GetWidth() const { return _width; }
	int GetHeight() const { return _height; }



	bool LoadTextureTGA(const char* textureFileName);

};