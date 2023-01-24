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
	player->posY += velocity; // 常にプレイヤーに重力をかける
	velocity -= gravity;      // 常に移動量に重力を加算する

	if (player->posY >= 0)    // ジャンプ中はジャンプできない
	{
		jump_flag = true;
	}
	else
	{
		jump_flag = false;
	}

	if (InputManager::On(KeyType::Right)) // 右
	{
		player->posX += move_speed;
	}
	if (InputManager::On(KeyType::Left))  // 左
	{
		player->posX -= move_speed;
	}
	if (InputManager::On(KeyType::Up))    // 奥
	{
		player->posZ += move_speed;
	}
	if (InputManager::On(KeyType::Down))  // 手前
	{
		player->posZ -= move_speed;
	}
	if (InputManager::Trg(KeyType::Space) && jump_flag == false) // ジャンプ
	{
		velocity = jump_hight;
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