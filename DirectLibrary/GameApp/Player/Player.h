#pragma once
#include"../ModelObject.h"

class Player
{
private:
	ModelObject* player = nullptr;
	float sizeX = 10.0f;
	float sizeY = 10.0f;
	float sizeZ = 10.0f;
	bool jump_flag = false;         // ジャンプフラグ(true→できる、false→できない)
	const float jump_hight = 30.0f; // ジャンプ高さ
	const float jump_speed = 0.05f; // ジャンプ速度
	const float gravity = 0.03f;    // 重力
	float vy = 0.0f;                // 移動量
	void Jump();
public:
	Player();
	~Player();
	void Start();
	void Update();
	void Render();
	Vector3 GetPosition();         // posを返す
	Vector3 GetSize();             // sizeを返す
	void SetPositon(Vector3 vec);  // posを変更する

};