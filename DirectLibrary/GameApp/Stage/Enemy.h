#pragma once
#include "../ModelObject.h"

class Enemy{
private:
	ModelObject* enemy;
	float sizeX = 10;
	float sizeY = 10;
	float sizeZ = 10;

	Vector3 pos = Vector3(enemy->posX, enemy->posY, enemy->posZ);
	Vector3 moveDirection;
	float moveSpeed;

	bool OutStageFlag;
	bool ActiveFlag;
public:
	Enemy();
	~Enemy();

	void SetUp(Vector3 SetPos, Vector3 SetDir, float SetSpd);

	void Start();
	void Update();
	void Render();

	Vector3 GetSize();
	
};