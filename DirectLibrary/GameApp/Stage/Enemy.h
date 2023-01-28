#pragma once
#include "../ModelObject.h"

class Enemy{
private:
	ModelObject* enemy;
	float sizeX = 0.5;
	float sizeY = 0.5;
	float sizeZ = 0.5;

	Vector3 pos;// = Vector3(enemy->posX, enemy->posY, enemy->posZ);
	Vector3 moveDirection;
	float moveSpeed;

	bool OutStageFlag;
	bool InitFlag;
public:
	Enemy();
	~Enemy();
	bool ActiveFlag;

	void SetUp(Vector3 SetPos, Vector3 SetDir, float SetSpd);

	void Start();
	void Update();
	void Render();

	Vector3 GetSize();

	//ê⁄êGÇµÇΩÇ©îªíËÇ∑ÇÈ
	bool IsHit(const Vector3& pos, const Vector3& size);
	
};