#include"EnemyManager.h"
#include <iostream>
EnemyManager::EnemyManager()
{
	srand((unsigned int)time(NULL)); // ŠÔ‚Å‰Šú‰»
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
	if (interval > 750)
	{
		interval -= 0.01f;;
	}

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
	Vector3 pos; // À•W
	Vector3 dir; // •ûŒü

	auto num = rand() % 4; // “G‚ÌoŒ»•ûŒü‚Ì—”
	auto rnd = rand() % 20 - 10;

	if (num == 0)
	{
		pos = Vector3(rnd,0,-10);
		dir = Vector3(0,0,1);   // ‰º‚©‚çoŒ»
		popCount++;
	}
	if (num == 1)
	{
		pos = Vector3(rnd,0,10);
		dir = Vector3(0,0,-1);  // ã‚©‚çoŒ»
		popCount++;
	}
	if (num == 2)
	{
		pos = Vector3(10,0,rnd);
		dir = Vector3(-1,0,0);  // ‰E‚©‚çoŒ»
		popCount++;
	}
	if (num == 3)
	{
		pos = Vector3(-10,0,rnd);
		dir = Vector3(1,0,0);   // ¶‚©‚çoŒ»
		popCount++;
	}

	auto spd = 0.001f + (popCount / 10) * 0.001f;
	if (spd > 0.011)
	{
		spd = 0.01;
	}
	auto createFlag = false;	//“GƒLƒƒƒ‰‚ğ¶¬‚µ‚½ƒtƒ‰ƒO‚ğOFF
	for (int i = 0; i < enemies.size(); ++i)
	{
		if (!enemies[i]->ActiveFlag)
		{
			//Šù‚É¶¬‚µ‚½“G‚©‚ÂŠù‚É“®ì‚ğI‚¦‚Ä‚¢‚é“G‚ğg‚¢‚Ü‚í‚·
			enemies[i]->SetUp(pos, dir, spd);
			createFlag = true;	//“GƒLƒƒƒ‰‚ğ¶¬‚µ‚½ƒtƒ‰ƒO‚ğON
			break;
		}
	}
	//“GƒLƒƒƒ‰‚ğ¶¬‚µ‚½ƒtƒ‰ƒO‚ªOFF= ‚Ü‚¾“G‚ğ¶¬‚µ‚Ä‚¢‚È‚¢ = Šù‘¶‚Ì“G‚ğg‚¢‚Ü‚í‚¹‚È‚¢
	if (!createFlag)
	{
		//“G‚ğV‹K‚Å¶¬‚·‚é
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

		//“G‚É“–‚½‚Á‚½‚©’²‚×‚é
		if (enemies[i]->IsHit(pos, size))
		{
			return true;
		}
	}
	return false;	//“G‚É“–‚½‚Á‚Ä‚È‚¢
}