#include "Texture2D.h"
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

Texture2D::Texture2D()
{

}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &_ID);
}

bool Texture2D::Load(char* path, int width, int height)
{
	char* tempTextureData; int fileSize; ifstream inFile;
	_width = width; _height = height;
	inFile.open(path, ios::binary);

	if (!inFile.good())
	{
		cerr << "Can't open texture file " << path << endl;
		return false;
	}

	inFile.seekg(0, ios::end); //seek to the end
	fileSize = (int)inFile.tellg(); //Get current pos in the file - the end in this case
	tempTextureData = new char[fileSize]; //Creates an array to store all the data
	inFile.seekg(0, ios::beg); //Goto beginning of the file
	inFile.read(tempTextureData, fileSize);//Read all data at once
	inFile.close();

	cout << path << " loaded" << endl;

	glGenTextures(1, &_ID); // Get the next texture ID
	glBindTexture(GL_TEXTURE_2D, _ID); // Bind texture to the ID
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);

	delete[]tempTextureData;//Clear up dthe data since its not needed
	return true;
}