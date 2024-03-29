#pragma once
#include "../ModelObject.h"
#include "../Stage/Enemy.h"
#include <vector>

class EnemyManager
{
private:
	float timeCount = 0.0f;   // 時間
	int popCount = 0;         // 出現した数
	float interval = 3600; // 発生間隔

	std::vector<Enemy*> enemies;
public:
	void Start();
	void Update();   // 処理
	void Render();	//描画
	void EnemyPop(); // 敵を生成する
	EnemyManager();
	~EnemyManager();
	bool IsHitEnemy(const Vector3& pos, const Vector3& size);
};