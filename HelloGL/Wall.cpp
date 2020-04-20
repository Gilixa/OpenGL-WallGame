#include "Wall.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include "Cube.h"
#include "MeshLoader.h"

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





	//for (int i = -3; i < 4; i++)
	//{
	//	
	//	for (int j = -3; j < 4; j++)
	//	{


	//		wallArray[k] = new Cube(cubeMesh, texture, i * 2, j * 2, _Zposition);

	//		k++;
	//	}
	//	
	//}


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

returnInts Wall::RollNumbers(int numberOfNumbers, int num1, int num2, int num3, int num4)
{
	int numberGenerator = rand() % numberOfNumbers + 1;
	int numberGenerator2;
	do
	{
		numberGenerator2 = rand() % numberOfNumbers + 1;
	} while (numberGenerator == numberGenerator2);

	returnInts numbers;


	switch (numberGenerator)
	{
	case 1:
		numbers.num1 = num1;
		break;
	case 2:
		numbers.num1 = num2;
		break;
	case 3:
		numbers.num1 = num3;
		break;
	case 4:
		numbers.num1 = num4;
		break;
	default:
		numbers.num1 = num1;
		cout << "Please enter the correct numberOfNumbers" << endl;
		break;
	}

	switch (numberGenerator2)
	{
	case 1:
		numbers.num2 = num1;
		break;
	case 2:
		numbers.num2 = num2;
		break;
	case 3:
		numbers.num2 = num3;
		break;
	case 4:
		numbers.num2 = num4;
		break;
	default:
		numbers.num2 = num1;
		cout << "Please enter the correct numberOfNumbers" << endl;
		break;
	}

	return numbers;
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