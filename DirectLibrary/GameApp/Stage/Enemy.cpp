#include "Enemy.h"
#include "Stage.h"

Enemy::Enemy()
{
	enemy = new ModelObject(L"Enemy.txt");

	pos = Vector3(0, 0, 0);
	moveDirection = Vector3(0, 0, 0);
	moveSpeed = 0.0f;

	OutStageFlag = false;
	ActiveFlag = false;
	InitFlag = false;
}

Enemy::~Enemy()
{
	delete enemy;
}

void Enemy::SetUp(Vector3 SetPos, Vector3 SetDir, float SetSpd)
{
	pos = SetPos;
	moveDirection = SetDir;
	moveSpeed = SetSpd;
	Start();
}

void Enemy::Start()
{
	InitFlag = true;
	ActiveFlag = true;

	enemy->posX = pos.x;
	enemy->posY = pos.y;
	enemy->posZ = pos.z;
	enemy->rotX = 100;
	enemy->rotY = 100;
	enemy->rotZ = 100;
	enemy->scaleX = 1;
	enemy->scaleY = 1;
	enemy->scaleZ = 1;
}

void Enemy::Update()
{
	if (ActiveFlag) {
		this->pos.x += moveDirection.x * moveSpeed;
		this->pos.y += moveDirection.y * moveSpeed;
		this->pos.z += moveDirection.z * moveSpeed;
	}
	else {
		moveSpeed = 0;
	}

	enemy->posX = pos.x;
	enemy->posY = pos.y;
	enemy->posZ = pos.z;

	auto flag = Stage::GetOutStageFlag(pos);//ステージの外にでたか判定フラグを取得する
	if (flag)
	{
		if (InitFlag)
		{
			//まだステージに入っていないので削除フラグのONは無視する
		}
		else
		{
			OutStageFlag = true;
		}
	}
	else
	{
		InitFlag = false;
	}

	if (OutStageFlag) {
		ActiveFlag = false;
	}
}

void Enemy::Render()
{
	enemy->Render();
}

Vector3 Enemy::GetSize()
{
	Vector3 size(sizeX, sizeY, sizeZ);
	return size;
}
