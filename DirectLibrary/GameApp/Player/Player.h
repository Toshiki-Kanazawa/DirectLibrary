#pragma once
#include"../ModelObject.h"

class Player
{
private:
	ModelObject* player = nullptr;
	float move_speed = 0.001f;         // �ړ����x
	float sizeX = 10.0f;
	float sizeY = 10.0f;
	float sizeZ = 10.0f;
	bool jump_flag = false;           // �W�����v�t���O (true���W�����v��)
	const float jump_hight = 0.01f;   // �W�����v����
	const double gravity = 0.00001f;    // �d��
	float velocity = 0.0f;            // �ړ���

public:
	Player();     // �R���X�g���N�^
	~Player();    // �f�X�g���N�^
	void Start();
	void Update();
	void Render();

	Vector3 GetPosition();         // pos��Ԃ�
	Vector3 GetSize();             // size��Ԃ�
	void SetPositon(Vector3 vec);  // pos��ύX����

};