#include "GameApp.h"
#include "../Library/DirectX/InputManager.h"
#include "../Library/Vector3.h"
#include "ModelObject.h"

//GameObject gameObject;
//GameObject gameObject2;

Camera GameApp::camera = {};

GameApp::GameApp(GameLibrary* gameLibrary)
{
    camera = Camera();
    camera.posX = 0.0f;
    camera.posY = 0.0f;
    camera.posZ = -2.0f;
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
    
    //gameObject.pos = Vector3(0, 0, 0);
    //gameObject.rot = Vector3(0, 0, 0);
    //gameObject.scale = Vector3(1, 1, 1);
    //gameObject2.pos.z = 10.0f;
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

	//scene->Update(1.0f);
	//gameLibrary->SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//if (InputManager::On(KeyType::A))
	//{
	//	gameLibrary->SetClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	//}
	//else if (InputManager::On(KeyType::S))
	//{
	//	gameLibrary->SetClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	//}

    //if (InputManager::On(KeyType::Left))
    //{
    //    gameObject.pos.x -= 0.01f;
    //    //camera.posX -= 0.01f;
    //    //camera.focusX -= 0.01f;
    //}
    //if (InputManager::On(KeyType::Right))
    //{
    //    gameObject.pos.x += 0.01f;
    //    //camera.posX += 0.01f;
    //    //camera.focusX += 0.01f;
    //}
    //if (InputManager::On(KeyType::Up))
    //{
    //    gameObject.pos.z += 0.01f;
    //    //camera.posZ += 0.01f;
    //    //camera.focusZ += 0.01f;
    //}
    //if (InputManager::On(KeyType::Down))
    //{
    //    gameObject.pos.z -= 0.01f;
    //    //camera.posZ -= 0.01f;
    //    //camera.focusZ -= 0.01f;
    //}

    if (InputManager::On(KeyType::W))
    {
        camera.posY += 0.01f;
    }
    //if (InputManager::On(KeyType::S))
    //{
    //    camera.posY -= 0.01f;
    //}

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

    //シーンの描画
    //scene->Render();
    
    //描画の反映
    gameLibrary->FinishRendering();

}

//TestScene::TestScene(GameLibrary* gameLibrary)
//{
//    auto data = VertexData();
//    data.vertex = vertexList;
//    data.indexes = indexList;
//    data.size = 24;
//    data.indexSize = 36;
//	mesh = gameLibrary->CreateMeshRenderer( &data );
//
//    mesh2 = gameLibrary->CreateMeshRenderer(&data);
//}
//
//TestScene::~TestScene()
//{
//	delete mesh;
//    delete mesh2;
//}
//
//void TestScene::Update( float deltaTime )
//{
//}
//
//void TestScene::Render()
//{
//    mesh->SetContextBuffer(gameObject, GameApp::GetCamera() );
//	//ここで三角形を描画したい
//	mesh->Draw();
//
//    mesh2->SetContextBuffer(gameObject2, GameApp::GetCamera());
//    mesh2->Draw();
//}