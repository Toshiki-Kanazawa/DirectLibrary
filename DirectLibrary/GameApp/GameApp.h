#pragma once
#include "../Library/GameLibrary.h"
#include "Player/Player.h"
#include "Stage/Stage.h"

//class IScene
//{
//public:
//	virtual void Update( float deltaTime ) = 0;
//	virtual void Render() = 0;
//};

class GameApp
{
private:
	GameLibrary* gameLibrary;
	//IScene* scene;
	static Camera camera;
public:
	GameApp(GameLibrary* gameLibrary);
	void Update();
	void Render();
	static const Camera& GetCamera(){ return camera; }
};