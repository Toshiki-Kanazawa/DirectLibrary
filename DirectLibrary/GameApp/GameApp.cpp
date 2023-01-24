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

    //�J������ݒ肷��
    ModelObject::camera = &camera;
    ModelObject::gameLib = gameLibrary;

    //�X�e�[�W�𐶐�����
    stage = new Stage();
    stage->Start();

    //�v���C���[�𐶐�����
    player = new Player();
    //player->Start();

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

    //�v���C���[�̍��W���C������
    auto pos = player->GetPosition();
    auto size = player->GetSize();
    pos = stage->GetPlayerNextPos(pos, size);
    player->SetPositon(pos);

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
    
    //�`��̔��f
    gameLibrary->FinishRendering();

}