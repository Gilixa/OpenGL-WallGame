#include "Wall.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include "Cube.h"
#include "MeshLoader.h"

using namespace std;


Wall::Wall(float z)
{
	z = _Zposition;

	Mesh* cubeMesh = MeshLoader::Load((char*)"Cube.txt");
	Texture2D* texture = new Texture2D();
	texture->Load((char*)"penguins.raw", 512, 512);

	int k = 0;

	for (int i = -3; i < 4; i++)
	{
		
		for (int j = -3; j < 4; j++)
		{


			wallArray[k] = new Cube(cubeMesh, texture, i * 2, j * 2, 3);

			k++;
		}
		
	}








}

Wall::~Wall()
{
	for (int i = 0; i < numberOfWallTiles; i++)
	{
		delete wallArray[i];
		wallArray[i] = NULL;

	}
}

void Wall::Draw()

{
	for (int i = 0; i < numberOfWallTiles; i++)
	{
		wallArray[i]->Draw();
	}
}

void Wall::GenerateWall()
{
	int wallArray[9] = { 0 };

	int numberGenerator = rand() % 9;
	int secondNumber;

	switch (numberGenerator)
	{
	case 0:
		secondNumber = RollNumbers(2, 1, 3, NULL, NULL);
		break;
	case 1:
		secondNumber = RollNumbers(3, 0, 2, 4, NULL);
		break;
	case 2:
		secondNumber = RollNumbers(2, 1, 5, NULL, NULL);
		break;
	case 3:
		secondNumber = RollNumbers(3, 0, 4, 6, NULL);
		break;
	case 4:
		secondNumber = RollNumbers(4, 1, 3, 5, 7);
		break;
	case 5:
		secondNumber = RollNumbers(3, 2, 4, 8, NULL);
		break;
	case 6:
		secondNumber = RollNumbers(2, 3, 7, NULL, NULL);
		break;
	case 7:
		secondNumber = RollNumbers(3, 4, 6, 8, NULL);
		break;
	case 8:
		secondNumber = RollNumbers(2, 5, 7, NULL, NULL);
		break;
	}

	wallArray[numberGenerator] = 1;
	wallArray[secondNumber] = 1;

}

int Wall::RollNumbers(int numberOfNumbers, int num1, int num2, int num3, int num4)
{
	int numberGenerator = rand() % numberOfNumbers + 1;

	switch (numberGenerator)
	{
	case 1:
		return num1;
		break;
	case 2:
		return num2;
		break;
	case 3:
		return num3;
		break;
	case 4:
		return num4;
		break;
	default:
		return num1;
		cout << "Please enter the correct numberOfNumbers" << endl;
		break;
	}
}