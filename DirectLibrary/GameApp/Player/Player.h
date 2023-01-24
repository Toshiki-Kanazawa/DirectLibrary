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
	Vector3 GetPosition(); // pos‚ğ•Ô‚·
	Vector3 GetSize();     // size‚ğ•Ô‚·
	void SetPositon(Vector3 vec);  // pos‚ğ•ÏX‚·‚é

};