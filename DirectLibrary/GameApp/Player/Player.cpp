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
	player->posX = 100;
	player->posY = 100;
	player->posZ = 100;
	player->rotX = 100;
	player->rotY = 100;
	player->rotZ = 100;
	player->scaleX = 1;
	player->scaleY = 1;
	player->scaleZ = 1;
}

void Player::Update()
{
	if (InputManager::On(KeyType::Right))
	{
		player->posX += 0.01f;
	}
	if (InputManager::On(KeyType::Left))
	{
		player->posX -= 0.01f;
	}
	if (InputManager::On(KeyType::Up))
	{
		player->posZ += 0.01f;
	}
	if (InputManager::On(KeyType::Down))
	{
		player->posZ -= 0.01f;
	}
	if (InputManager::On(KeyType::Space))
	{
	 
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
