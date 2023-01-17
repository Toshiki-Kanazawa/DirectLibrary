#include"Player.h"

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
	player->scaleX = 100;
	player->scaleY = 100;
	player->scaleZ = 100;
}

void Player::Update()
{

}

void Player::Render()
{

}
