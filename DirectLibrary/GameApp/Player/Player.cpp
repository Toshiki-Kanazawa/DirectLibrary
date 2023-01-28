#include"Player.h"
#include "../../Library/DirectX/InputManager.h"

Player::Player()
{
	player = new ModelObject(L"Player.txt");
}

Player::~Player()
{
	delete player;
}

void Player::Start()
{
	player->posX = 0.0f;
	player->posY = 0.0f;
	player->posZ = 0.0f;
	player->rotX = 0.0f;
	player->rotY = 0.0f;
	player->rotZ = 0.0f;
	player->scaleX = 1.0f;
	player->scaleY = 1.0f;
	player->scaleZ = 1.0f;
}

void Player::Update()
{
	player->posY += velocity; // ��Ƀv���C���[�ɏd�͂�������
	velocity -= gravity;      // ��Ɉړ��ʂɏd�͂����Z����

	if (player->posY - sizeY <= 0.0f )
	{
		jump_flag = true;
	}

	if (InputManager::On(KeyType::Right)) // �E
	{
		player->posX += move_speed;
	}
	if (InputManager::On(KeyType::Left))  // ��
	{
		player->posX -= move_speed;
	}
	if (InputManager::On(KeyType::Up))    // ��
	{
		player->posZ += move_speed;
	}
	if (InputManager::On(KeyType::Down))  // ��O
	{
		player->posZ -= move_speed;
	}
	if (InputManager::Trg(KeyType::Z) ) // �W�����v
	{
		if (jump_flag)
		{
			velocity = jump_hight;
			jump_flag = false;
		}
	}
}

void Player::Render()
{
	player->Render();
}

Vector3 Player::GetPosition()
{
	Vector3 pos(player->posX, player->posY, player->posZ);
	return pos;
}

Vector3 Player::GetSize()
{
	Vector3 size(sizeX, sizeY, sizeZ);
	return size;
}

void Player::SetPositon(Vector3 vec)
{
	player->posX = vec.x;
	player->posY = vec.y;
	player->posZ = vec.z;
}