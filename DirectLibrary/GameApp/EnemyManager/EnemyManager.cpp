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
	Vector3 pos; // ���W
	Vector3 dir; // ����

	auto num = rand() % 4; // �G�̏o�������̗���
	auto rnd = rand() % 20 - 10;

	if (num == 0)
	{
		pos = Vector3(rnd,0,-10);
		dir = Vector3(0,0,1);   // ������o��
		popCount++;
	}
	if (num == 1)
	{
		pos = Vector3(rnd,0,10);
		dir = Vector3(0,0,-1);  // �ォ��o��
		popCount++;
	}
	if (num == 2)
	{
		pos = Vector3(10,0,rnd);
		dir = Vector3(-1,0,0);  // �E����o��
		popCount++;
	}
	if (num == 3)
	{
		pos = Vector3(-10,0,rnd);
		dir = Vector3(1,0,0);   // ������o��
		popCount++;
	}

	auto spd = 0.001f + (popCount / 10) * 0.001f;
	auto createFlag = false;	//�G�L�����𐶐������t���O��OFF
	for (int i = 0; i < enemies.size(); ++i)
	{
		if (!enemies[i]->ActiveFlag)
		{
			//���ɐ��������G�����ɓ�����I���Ă���G���g���܂킷
			enemies[i]->SetUp(pos, dir, spd);
			createFlag = true;	//�G�L�����𐶐������t���O��ON
			break;
		}
	}
	//�G�L�����𐶐������t���O��OFF= �܂��G�𐶐����Ă��Ȃ� = �����̓G���g���܂킹�Ȃ�
	if (!createFlag)
	{
		//�G��V�K�Ő�������
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

		//�G�ɓ������������ׂ�
		if (enemies[i]->IsHit(pos, size))
		{
			return true;
		}
	}
	return false;	//�G�ɓ������ĂȂ�
}