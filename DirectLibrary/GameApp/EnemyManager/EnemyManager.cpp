#include"EnemyManager.h"
#include <iostream>
EnemyManager::EnemyManager()
{
}
EnemyManager::~EnemyManager()
{
}

void EnemyManager::Start()
{
	timeCount = 0;
	popCount = 0;
	for (int i = 0; i < enemies.size(); ++i)
	{
		enemies[i]->ActiveFlag = false;
	}
}

void EnemyManager::Update()
{
	timeCount++;

	if (timeCount >= interval)
	{
		EnemyPop();
		timeCount = 0;
	}

	for (int i = 0; i < enemies.size(); ++i)
	{
		if (enemies[i]->ActiveFlag)
		{
			enemies[i]->Update();
		}
	}
}

void EnemyManager::Render()
{
	for (int i = 0; i < enemies.size(); ++i)
	{
		if (enemies[i]->ActiveFlag)
		{
			enemies[i]->Render();
		}
	}
}

void EnemyManager::EnemyPop()
{
	Vector3 pos; // 座標
	Vector3 dir; // 方向

	auto num = rand() % 4; // 敵の出現方向の乱数
	auto rnd = rand() % 20 - 10;

	if (num == 0)
	{
		pos = Vector3(rnd,0,-10);
		dir = Vector3(0,0,1);   // 下から出現
		popCount++;
	}
	if (num == 1)
	{
		pos = Vector3(rnd,0,10);
		dir = Vector3(0,0,-1);  // 上から出現
		popCount++;
	}
	if (num == 2)
	{
		pos = Vector3(10,0,rnd);
		dir = Vector3(-1,0,0);  // 右から出現
		popCount++;
	}
	if (num == 3)
	{
		pos = Vector3(-10,0,rnd);
		dir = Vector3(1,0,0);   // 左から出現
		popCount++;
	}

	auto spd = 0.001f + (popCount / 10) * 0.001f;
	auto createFlag = false;	//敵キャラを生成したフラグをOFF
	for (int i = 0; i < enemies.size(); ++i)
	{
		if (!enemies[i]->ActiveFlag)
		{
			//既に生成した敵かつ既に動作を終えている敵を使いまわす
			enemies[i]->SetUp(pos, dir, spd);
			createFlag = true;	//敵キャラを生成したフラグをON
			break;
		}
	}
	//敵キャラを生成したフラグがOFF= まだ敵を生成していない = 既存の敵を使いまわせない
	if (!createFlag)
	{
		//敵を新規で生成する
		auto enemy = new Enemy();
		enemy->SetUp(pos, dir, spd);
		enemies.emplace_back(enemy);
	}
}

bool EnemyManager::IsHitEnemy(const Vector3& pos, const Vector3& size)
{
	for (int i = 0; i < enemies.size(); ++i)
	{
		if (!enemies[i]->ActiveFlag) continue;

		//敵に当たったか調べる
		if (enemies[i]->IsHit(pos, size))
		{
			return true;
		}
	}
	return false;	//敵に当たってない
}