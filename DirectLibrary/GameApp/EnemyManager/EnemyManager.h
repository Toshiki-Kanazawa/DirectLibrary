#pragma once
#include"../ModelObject.h"
class EnemyManager
{
private:
	float timeCount = 0.0f; // ����
	float speed = 1.0f;     // �o���Ԋu
	int popCount = 0;       // �o��������
public:
	void Update();   // ����
	void EnemyPop(); // �G�𐶐�����
};