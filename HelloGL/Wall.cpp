#include "Wall.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include "Cube.h"
#include "MeshLoader.h"
#include "Player.h"

using namespace std;

int wallLookupArray[7][7] =
{
	{0,1,2,3,4,5,6},
	{7,8,9,10,11,12,13},
	{14,15,16,17,18,19,20},
	{21,22,23,24,25,26,27},
	{28,29,30,31,32,33,34},
	{35,36,37,38,39,40,41},
	{42,43,44,45,46,47,48}
};

Wall::Wall(float z)
{
	_Zposition = z;
	numberOfTiles = 49;
	GenerateWall();

}

Wall::~Wall()
{
	for (int i = 0; i < numberOfTiles; i++)
	{
		delete wallArray[i];
		wallArray[i] = NULL;
	}

}

void Wall::Draw()

{
	for (int i = 0; i < numberOfTiles; i++)
	{
		wallArray[i]->Draw();
	}
}

void Wall::Update()
{

}

void Wall::GenerateWall()
{
	int numberGenerator = rand() % 48 + 1;
	int inputNumber1 = GetPos(numberGenerator).num1;
	int inputNumber2 = GetPos(numberGenerator).num2;
	int wallArrayTest[7][7] = { 0 };

	wallArrayTest[inputNumber2][inputNumber1] = 1;

	if (inputNumber1 == 0)
	{
		wallArrayTest[inputNumber2][inputNumber1 + 1] = 1;
	}
	else if (inputNumber1 == 6)
	{
		wallArrayTest[inputNumber2][inputNumber1 - 1] = 1;
	}
	else
	{
		wallArrayTest[inputNumber2][inputNumber1 + 1] = 1;
		wallArrayTest[inputNumber2][inputNumber1 - 1] = 1;
	}

	if (inputNumber2 == 0)
	{
		wallArrayTest[inputNumber2 + 1][inputNumber1] = 1;
	}
	else if (inputNumber2 == 6)
	{
		wallArrayTest[inputNumber2 - 1][inputNumber1] = 1;
	}
	else
	{
		wallArrayTest[inputNumber2 + 1][inputNumber1] = 1;
		wallArrayTest[inputNumber2 - 1][inputNumber1] = 1;
	}

	Mesh* cubeMesh = MeshLoader::Load((char*)"Cube.txt");
	Texture2D* texture = new Texture2D();
	texture->Load((char*)"penguins.raw", 512, 512);
	int k = 0;
	int x = -3;
	int y = -3;

	
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (wallArrayTest[i][j] == 0)
			{
				wallArray[k] = new Cube(cubeMesh, texture, x * 2, y * 2, _Zposition);

				k++;

			}
			else
			{
				numberOfTiles--;
			}

			y++;
		}
		y = -3;

		x++;
	}

}

returnInts Wall::GetPos(int num1)
{
	returnInts numbers;

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (num1 == wallLookupArray[j][i])
			{
				numbers.num1 = i;
				numbers.num2 = j;
				return numbers;
			}

		}
	}

}

bool Wall::WallCollision(Player* s1)
{
	//Objects collision
	for (int i = 0; i < numberOfTiles; i++)
	{
		wallArray[i]->Update();
		for (int j = 0; j < 2; j++)
		{
			float distance = CalculateDistanceSquared(s1, wallArray[i]);
			float widthDistance = s1->_width + wallArray[i]->GetWidth();

			if (distance <= widthDistance)
			{
				return true;
			}
		}
	}
	
	return false;

}

float Wall::CalculateDistanceSquared(Player* s1, SceneObject* s2)
{
	float distance = ((s1->_position.x - s2->_position.x) * (s1->_position.x - s2->_position.x)) + ((s1->_position.y - s2->_position.y) * (s1->_position.y - s2->_position.y)) + ((s1->_position.z - s2->_position.z) * (s1->_position.z - s2->_position.z));

	return distance;
}
