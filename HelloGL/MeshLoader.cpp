#include "MeshLoader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


using namespace std;

namespace MeshLoader
{
	void LoadVertices(ifstream& inFile, Mesh& mesh);
	void LoadColours(ifstream& inFile, Mesh& mesh);
	void LoadIndices(ifstream& inFile, Mesh& mesh);
	void LoadCoords(ifstream& inFile, Mesh& mesh);
	void LoadNormal(ifstream& inFile, Mesh& mesh);

	void LoadVertices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.VertexCount;

		if (mesh.VertexCount > 0)
		{
			mesh.Vertices = new Vertex[mesh.VertexCount];

			for (int i = 0; i < mesh.VertexCount; i++)
			{
				inFile >> mesh.Vertices[i].x;
				inFile >> mesh.Vertices[i].y;
				inFile >> mesh.Vertices[i].z;
			}
		}

	}

	//void LoadColours(ifstream& inFile, Mesh& mesh)
	//{
	//	inFile >> mesh.ColorCount;

	//	if (mesh.ColorCount > 0)
	//	{
	//		mesh.Colors = new Color[mesh.ColorCount];

	//		for (int i = 0; i < mesh.ColorCount; i++)
	//		{
	//			inFile >> mesh.Colors[i].r;
	//			inFile >> mesh.Colors[i].g;
	//			inFile >> mesh.Colors[i].b;
	//		}
	//	}

	//}

	void LoadCoords(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.TexCoordCount;

		if (mesh.TexCoordCount > 0)
		{
			mesh.TexCoords = new TexCoord[mesh.TexCoordCount];

			for (int i = 0; i < mesh.TexCoordCount; i++)
			{
				inFile >> mesh.TexCoords[i].u;
				inFile >> mesh.TexCoords[i].v;
			}
		}

	}

	void LoadIndices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.IndexCount;

		if (mesh.IndexCount > 0)
		{
			mesh.Indices = new GLushort[mesh.IndexCount];

			for (int i = 0; i < mesh.IndexCount / 3; i++)
			{
				inFile >> mesh.Indices[(i * 3)];
				inFile >> mesh.Indices[(i * 3) + 1];
				inFile >> mesh.Indices[(i * 3) + 2];
			}
		}
	}

	void LoadNormal(ifstream& inFile, Mesh& mesh)
	{
		
		inFile >> mesh.NormalCount;

		if (mesh.NormalCount > 0)
		{
			mesh.Normals = new Vector3[mesh.NormalCount];
			for (int i = 0; i < mesh.NormalCount; i++)
			{


				inFile >> mesh.Normals[i].x;
				inFile >> mesh.Normals[i].y;
				inFile >> mesh.Normals[i].z;

			}
		}
	}

	Mesh* MeshLoader::Load(char* path)
	{
		Mesh* mesh = new Mesh();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())
		{
			cerr << "Can't open texture file " << path << endl;
			return nullptr;
		}

		LoadVertices(inFile, *mesh);
		//LoadColours(inFile, *mesh);
		LoadCoords(inFile, *mesh);
		LoadNormal(inFile, *mesh);
		LoadIndices(inFile, *mesh);

		return mesh;
	}

	TexturedMesh* MeshLoader::LoadTextured(char* path)
	{
		TexturedMesh* mesh = new TexturedMesh();
		mesh->Mesh = new Mesh();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())
		{
			cerr << "Can't open texture file " << path << endl;
			return nullptr;
		}

		LoadVertices(inFile, *mesh->Mesh);
		//LoadColours(inFile, *mesh->Mesh);
		LoadCoords(inFile, *mesh->Mesh);
		LoadNormal(inFile, *mesh->Mesh);
		LoadIndices(inFile, *mesh->Mesh);

		


		return mesh;
	}
}
