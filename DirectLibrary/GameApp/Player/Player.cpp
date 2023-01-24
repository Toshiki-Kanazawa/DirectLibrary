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
	vy = 0.0f;

	if (player->posY > 0)    // ジャンプ中
	{
		jump_flag = false;  // ジャンプできない

		vy += gravity;      // 移動量に重力を加える
		player->posY -= vy; // プレイヤーに重力を加える
	}

	if (InputManager::On(KeyType::Right)) // 右
	{
		player->posX += 0.01f;
	}
	if (InputManager::On(KeyType::Left))  // 左
	{
		player->posX -= 0.01f;
	}
	if (InputManager::On(KeyType::Up))    // 奥
	{
		player->posZ += 0.01f;
	}
	if (InputManager::On(KeyType::Down))  // 手前
	{
		player->posZ -= 0.01f;
	}
	if (InputManager::On(KeyType::Space)) // ジャンプ
	{
		if (!jump_flag)
		{
			Jump();
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

void Player::Jump()
{
	jump_flag = true;

	if (player->posY < jump_hight)
	{
		player->posY += jump_speed;
	}
}