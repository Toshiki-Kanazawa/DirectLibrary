#include "GameApp.h"
#include "../Library/DirectX/InputManager.h"
#include "../Library/Vector3.h"
#include "ModelObject.h"

Camera GameApp::camera = {};

GameApp::GameApp(GameLibrary* gameLibrary)
{
    camera = Camera();
    camera.posX = 0.0f;
    camera.posY = 50.0f;
    camera.posZ = -50.0f;
    camera.focusX = 0.0f;
    camera.focusY = 0.0f;
    camera.focusZ = 0.0f;
	this->gameLibrary = gameLibrary;
	//scene = new TestScene( gameLibrary );

    //カメラを設定する
    ModelObject::camera = &camera;
    ModelObject::gameLib = gameLibrary;

    //ステージを生成する
    stage = new Stage();
    stage->Start();

    //プレイヤーを生成する
    player = new Player();
    //player->Start();

}

//ゲームの更新処理(毎フレーム呼ばれる)
void GameApp::Update()
{
    gameLibrary->UpdateCamera(camera);

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
    
    //描画の反映
    gameLibrary->FinishRendering();

}