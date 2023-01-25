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
	Vector3 pos; // ���W
	Vector3 dir; // ����

	auto num = rand() % 3; // �G�̏o�������̗���

	if (num == 0)
	{
		pos = Vector3(0,0,-10);
		dir = Vector3(0,0,-1); // ������o��
		//enemy->Setup(dir,pos)
	}
	if (num == 1)
	{
		pos = Vector3(0,0,10);
		dir = Vector3(0,0,1);  // �ォ��o��
		//enemy->Setup(dir,pos)
	}
	if (num == 2)
	{
		pos = Vector3(10,0,0);
		dir = Vector3(1,0,0);  // �E����o��
		//enemy->Setup(dir,pos)
	}
	if (num == 3)
	{
		pos = Vector3(-10,0,0);
		dir = Vector3(-1,0,0); // ������o��
		//enemy->Setup(dir,pos)
	}

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