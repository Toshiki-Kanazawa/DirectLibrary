#pragma once
#include "../ModelObject.h"
#include "../Stage/Enemy.h"
#include <vector>

class EnemyManager
{
private:
	float timeCount = 0.0f;   // ����
	int popCount = 0;         // �o��������
	float interval = 3600; // �����Ԋu

	std::vector<Enemy*> enemies;
public:
	void Update();   // ����
	void Render();	//�`��
	void EnemyPop(); // �G�𐶐�����
	EnemyManager();
	~EnemyManager();
};