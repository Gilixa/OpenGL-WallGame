#pragma once
#include "SceneObject.h"

class Player : public SceneObject
{
private:
	Material* _material;

public:
	Player(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~Player();

	void Draw();
	void Update();

	void SetUpMaterial();

	void SetRotation(float rotation);



	Vector3 GetPosition();
	void SetPosition(Vector3 position);

	void Keyboard(unsigned char key, int x, int y);


};

