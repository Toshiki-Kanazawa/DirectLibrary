#include "GameApp.h"
#include "../Library/DirectX/InputManager.h"

Vertex vertexList[]
{
    Vertex( -0.2f,  0.2f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f ),
	Vertex( 0.2f, -0.2f, 0.0f , 1.0f, 1.0f, 1.0f, 1.0f ),
	Vertex( -0.2f, -0.2f, 0.0f , 1.0f, 1.0f, 1.0f, 1.0f),
};


GameApp::GameApp(GameLibrary* gameLibrary)
{
	this->gameLibrary = gameLibrary;
	scene = new TestScene( gameLibrary );
}

void GameApp::Update()
{
	InputManager::Update();
	scene->Update(1.0f);

	gameLibrary->SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	if (InputManager::On(KeyType::A))
	{
		gameLibrary->SetClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else if (InputManager::On(KeyType::S))
	{
		gameLibrary->SetClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	}

}

void GameApp::Render()
{
	//�`��̊J�n
	gameLibrary->StartRendering();

	//�V�[���̕`��
	scene->Render();

	//�`��̏I��(��ʂ֔��f����)
	gameLibrary->FinishRendering();
}

TestScene::TestScene(GameLibrary* gameLibrary)
{
	mesh = gameLibrary->CreateMeshRenderer( vertexList, 3 );
}

TestScene::~TestScene()
{
	delete mesh;
}

void TestScene::Update( float deltaTime )
{
}

void TestScene::Render()
{
	//�����ŎO�p�`��`�悵����
	mesh->Draw();
}