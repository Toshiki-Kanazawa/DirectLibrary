#include"EnemyManager.h"
#include <iostream>
EnemyManager::EnemyManager()
{
}
EnemyManager::~EnemyManager()
{
}

void EnemyManager::Update()
{
	timeCount += speed;

	speed = 3.0f + (popCount / 10) * 1.0f;

	if (timeCount >= 60)
	{
		EnemyPop();
		timeCount = 0;
	}
}

void EnemyManager::EnemyPop()
{
	Vector3 pos; // 座標
	Vector3 dir; // 方向

	auto num = rand() % 3; // 敵の出現方向の乱数

	if (num == 0)
	{
		pos = Vector3(0,0,-10);
		dir = Vector3(0,0,-1); // 下から出現
		//enemy->Setup(dir,pos)
	}
	if (num == 1)
	{
		pos = Vector3(0,0,10);
		dir = Vector3(0,0,1);  // 上から出現
		//enemy->Setup(dir,pos)
	}
	if (num == 2)
	{
		pos = Vector3(10,0,0);
		dir = Vector3(1,0,0);  // 右から出現
		//enemy->Setup(dir,pos)
	}
	if (num == 3)
	{
		pos = Vector3(-10,0,0);
		dir = Vector3(-1,0,0); // 左から出現
		//enemy->Setup(dir,pos)
	}
}