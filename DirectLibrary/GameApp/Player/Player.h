#pragma once
#include"../ModelObject.h"

class Player
{
private:
	ModelObject* player = nullptr;
	float sizeX = 10.0f;
	float sizeY = 10.0f;
	float sizeZ = 10.0f;
	bool jump_flag = false; // ジャンプ中フラグ
	float jump_hight = 10.0f; // ジャンプ高さ
	float jump_speed = 0.05f;
	const float gravity = 0.02f; // 重力

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