#pragma once
#include"../ModelObject.h"

class Player
{
private:
	//ModelObject* player = nullptr;
public:
	Player();
	~Player();
	void Start();
	void Update();
	void Render();
};