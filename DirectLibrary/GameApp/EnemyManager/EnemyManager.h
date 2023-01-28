#pragma once
#include "../ModelObject.h"
#include "../Stage/Enemy.h"
#include <vector>

class EnemyManager
{
private:
	float timeCount = 0.0f;   // ŠÔ
	int popCount = 0;         // oŒ»‚µ‚½”
	float interval = 3600; // ”­¶ŠÔŠu

	std::vector<Enemy*> enemies;
public:
	void Start();
	void Update();   // ˆ—
	void Render();	//•`‰æ
	void EnemyPop(); // “G‚ğ¶¬‚·‚é
	EnemyManager();
	~EnemyManager();
	bool IsHitEnemy(const Vector3& pos, const Vector3& size);
};