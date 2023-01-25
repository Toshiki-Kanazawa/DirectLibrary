#pragma once
#include"../ModelObject.h"
class EnemyManager
{
private:
	float timeCount = 0.0f; // ŠÔ
	float speed = 1.0f;     // oŒ»ŠÔŠu
	int popCount = 0;       // oŒ»‚µ‚½”
public:
	void Update();   // ˆ—
	void EnemyPop(); // “G‚ğ¶¬‚·‚é
};