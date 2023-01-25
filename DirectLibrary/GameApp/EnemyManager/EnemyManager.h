#pragma once
#include "../ModelObject.h"
#include "../Stage/Enemy.h"
#include <vector>

class EnemyManager
{
private:
	float timeCount = 0.0f; // 時間
	float speed = 1.0f;     // 出現間隔
	int popCount = 0;       // 出現した数
	std::vector<Enemy*> enemies;
public:
	void Update();   // 処理
	void EnemyPop(); // 敵を生成する
	EnemyManager();
	~EnemyManager();
};