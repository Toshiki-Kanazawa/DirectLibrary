#pragma once
#include"../ModelObject.h"

class Player
{
private:
	ModelObject* player = nullptr;
	float sizeX = 10;
	float sizeY = 10;
	float sizeZ = 10;
public:
	Player();
	~Player();
	void Start();
	void Update();
	void Render();
	Vector3 GetPosition(); // posを返す
	Vector3 GetSize();     // sizeを返す
	void SetPositon(Vector3 vec);  // posを変更する

};