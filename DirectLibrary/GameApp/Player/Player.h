#pragma once
#include"../ModelObject.h"

class Player
{
private:
	ModelObject* player = nullptr;
	float move_speed = 0.001f;         // 移動速度
	float sizeX = 10.0f;
	float sizeY = 10.0f;
	float sizeZ = 10.0f;
	bool jump_flag = false;           // ジャンプフラグ (true→ジャンプ中)
	const float jump_hight = 0.01f;   // ジャンプ高さ
	const double gravity = 0.00001f;    // 重力
	float velocity = 0.0f;            // 移動量

public:
	Player();     // コンストラクタ
	~Player();    // デストラクタ
	void Start();
	void Update();
	void Render();

	Vector3 GetPosition();         // posを返す
	Vector3 GetSize();             // sizeを返す
	void SetPositon(Vector3 vec);  // posを変更する

};