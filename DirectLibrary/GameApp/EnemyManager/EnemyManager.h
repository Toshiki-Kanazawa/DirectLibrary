#pragma once
#include "../ModelObject.h"
#include "../Stage/Enemy.h"
#include <vector>

class EnemyManager
{
private:
	float timeCount = 0.0f; // ����
	float speed = 1.0f;     // �o���Ԋu
	int popCount = 0;       // �o��������
	std::vector<Enemy*> enemies;
public:
	void Update();   // ����
	void EnemyPop(); // �G�𐶐�����
	EnemyManager();
	~EnemyManager();
};