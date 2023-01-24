#pragma once
#include"../ModelObject.h"

class Player
{
private:
	ModelObject* player = nullptr;
	float sizeX = 10.0f;
	float sizeY = 10.0f;
	float sizeZ = 10.0f;
	bool jump_flag = false; // �W�����v���t���O
	float jump_hight = 10.0f; // �W�����v����
	float jump_speed = 0.05f;
	const float gravity = 0.02f; // �d��

	void Jump();
public:
	Player();
	~Player();
	void Start();
	void Update();
	void Render();
	Vector3 GetPosition();         // pos��Ԃ�
	Vector3 GetSize();             // size��Ԃ�
	void SetPositon(Vector3 vec);  // pos��ύX����

};