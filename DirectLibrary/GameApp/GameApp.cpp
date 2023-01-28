#include "GameApp.h"
#include "../Library/DirectX/InputManager.h"
#include "../Library/Vector3.h"
#include "ModelObject.h"

float Camera::posX = 0.0f;
float Camera::posY = 15.0f;
float Camera::posZ = -20.0f;
float Camera::focusX = 0.0f;
float Camera::focusY = 0.0f;
float Camera::focusZ = 0.0f;

GameApp::GameApp(GameLibrary* gameLibrary)
{
	this->gameLibrary = gameLibrary;
	//scene = new TestScene( gameLibrary );

    //カメラを設定する
    ModelObject::gameLib = gameLibrary;

    //ステージを生成する
    stage = new Stage();
    stage->Start();

    //プレイヤーを生成する
    player = new Player();
    //player->Start();

    //敵キャラマネージャを生成する
    enemyManager = new EnemyManager();

}

//ゲームの更新処理(毎フレーム呼ばれる)
void GameApp::Update()
{
    //入力の更新
	InputManager::Update();

    //ステージの更新
    stage->Update();

    //プレイヤーの更新
    player->Update();

    //プレイヤーの座標を修正する
    auto pos = player->GetPosition();
    auto size = player->GetSize();
    pos = stage->GetPlayerNextPos(pos, size);
    player->SetPositon(pos);

    //敵キャラの更新
    enemyManager->Update();

}

//ゲームの描画処理(毎フレーム呼ばれる)
void GameApp::Render()
{
    //描画の初期化
    gameLibrary->StartRendering();

    //ステージの描画
    stage->Render();

    //プレイヤーの描画
    player->Render();

    //敵キャラの描画
    enemyManager->Render();
    
    //描画の反映
    gameLibrary->FinishRendering();

}