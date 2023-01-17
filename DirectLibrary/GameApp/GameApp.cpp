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

    //�J������ݒ肷��
    ModelObject::camera = &camera;
    ModelObject::gameLib = gameLibrary;

    //�X�e�[�W�𐶐�����
    stage = new Stage();
    stage->Start();

    //�v���C���[�𐶐�����
    player = new Player();
    
    //gameObject.pos = Vector3(0, 0, 0);
    //gameObject.rot = Vector3(0, 0, 0);
    //gameObject.scale = Vector3(1, 1, 1);
    //gameObject2.pos.z = 10.0f;
}

//�Q�[���̍X�V����(���t���[���Ă΂��)
void GameApp::Update()
{
    gameLibrary->UpdateCamera(camera);

    //���͂̍X�V
	InputManager::Update();

    //�X�e�[�W�̍X�V
    stage->Update();

    //�v���C���[�̍X�V
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

//�Q�[���̕`�揈��(���t���[���Ă΂��)
void GameApp::Render()
{
    

    //�`��̏�����
    gameLibrary->StartRendering();

    //�X�e�[�W�̕`��
    stage->Render();

    //�v���C���[�̕`��
    player->Render();

    //�V�[���̕`��
    //scene->Render();
    
    //�`��̔��f
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
//	//�����ŎO�p�`��`�悵����
//	mesh->Draw();
//
//    mesh2->SetContextBuffer(gameObject2, GameApp::GetCamera());
//    mesh2->Draw();
//}