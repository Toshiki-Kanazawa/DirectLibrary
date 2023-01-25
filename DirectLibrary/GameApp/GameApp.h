#pragma once
#include "../Library/GameLibrary.h"
#include "Player/Player.h"
#include "Stage/Stage.h"
#include "EnemyManager/EnemyManager.h"
#include "../Library/DirectX/InputManager.h"

class GameApp
{
private:
	GameLibrary* gameLibrary;
	static Camera camera;

	Player* player;	//プレイヤー
	Stage* stage;	//ステージ
	EnemyManager* enemyManager;	//敵キャラマネージャ
public:
	GameApp(GameLibrary* gameLibrary);
	void Update();
	void Render();
	static const Camera& GetCamera(){ return camera; }
};