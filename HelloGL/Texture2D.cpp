
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



bool Texture2D::LoadTextureTGA(const char* textureFileName)
{
	char* tempHeaderData = new char[18]; //18 Bytes is TGA Header Size
	char* tempTextureData;
	int fileSize, type, pixelDepth, mode;

	ifstream inFile;

	inFile.open(textureFileName, ios::binary);
	if (!inFile.good())
	{
		cerr << "Can't open texture file " << textureFileName << endl;
		return -1;
	}

	//18 Bytes is the size of a TGA Header
	inFile.seekg(0, ios::beg); //Seek back to beginning of file
	inFile.read(tempHeaderData, 18); //Read in all the data in one go

	inFile.seekg(0, ios::end); //Seek to end of file
	fileSize = (int)inFile.tellg() - 18; //Get current position in file - The End, this gives us total file size
	tempTextureData = new char[fileSize]; //Create an new aray to store data
	inFile.seekg(18, ios::beg); //Seek back to beginning of file + 18
	inFile.read(tempTextureData, fileSize); //Read in all the data in one go
	inFile.close(); //Close the file

	type = (int)tempHeaderData[2]; //Get TGA Type out of Header - Must be RGB for this to work
	_width = ((unsigned char)tempHeaderData[13] << 8u) + (unsigned char)tempHeaderData[12]; // Find the width (Combines two bytes into a short)
	_height = ((unsigned char)tempHeaderData[15] << 8u) + (unsigned char)tempHeaderData[14]; //Find the height
	pixelDepth = (int)tempHeaderData[16]; // Find the pixel depth (24/32bpp)

	bool flipped = false;
	if ((int)((tempHeaderData[11] << 8) + tempHeaderData[10]) == 0)
		flipped = true;

	//We only support RGB type
	if (type == 2)
	{
		glGenTextures(1, &_ID); //Get next Texture ID
		glBindTexture(GL_TEXTURE_2D, _ID); //Bind the texture to the ID

		mode = pixelDepth / 8;

		//Note that TGA files are stored as BGR(A) - So we need to specify the format as GL_BGR(A)_EXT
		if (mode == 4)
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, _width, _height, GL_BGRA_EXT, GL_UNSIGNED_BYTE, tempTextureData);
		else
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, _width, _height, GL_BGR_EXT, GL_UNSIGNED_BYTE, tempTextureData);
	}
	else
	{
		cout << "Incorrect TGA type, must be RGB" << endl;
	}

delete[] tempHeaderData; //We don't need the header memory anymore
delete[] tempTextureData; //Clear up the data - We don't need this any more

return true;
}