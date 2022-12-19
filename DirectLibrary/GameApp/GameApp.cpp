#include "GameApp.h"
#include "../Library/DirectX/InputManager.h"

Vertex vertexList[]
{
    Vertex(-0.5f,  0.5f, -0.5f , 1.0f, 0.0f, 0.0f, 1.0f ),
    Vertex( 0.5f,  0.5f, -0.5f , 1.0f, 0.0f, 0.0f, 1.0f ),
    Vertex(-0.5f, -0.5f, -0.5f , 1.0f, 0.0f, 0.0f, 1.0f ),
    Vertex( 0.5f, -0.5f, -0.5f , 1.0f, 0.0f, 0.0f, 1.0f ),
    Vertex(-0.5f,  0.5f,  0.5f , 0.0f, 1.0f, 1.0f, 1.0f ),
    Vertex(-0.5f, -0.5f,  0.5f , 0.0f, 1.0f, 1.0f, 1.0f ),
    Vertex( 0.5f,  0.5f,  0.5f , 0.0f, 1.0f, 1.0f, 1.0f ),
    Vertex( 0.5f, -0.5f,  0.5f , 0.0f, 1.0f, 1.0f, 1.0f ),
    Vertex(-0.5f,  0.5f,  0.5f , 1.0f, 1.0f, 0.0f, 1.0f ),
    Vertex(-0.5f,  0.5f, -0.5f , 1.0f, 1.0f, 0.0f, 1.0f ),
    Vertex(-0.5f, -0.5f,  0.5f , 1.0f, 1.0f, 0.0f, 1.0f ),
    Vertex(-0.5f, -0.5f, -0.5f , 1.0f, 1.0f, 0.0f, 1.0f ),
    Vertex( 0.5f,  0.5f,  0.5f , 0.0f, 0.0f, 1.0f, 1.0f ),
    Vertex( 0.5f, -0.5f,  0.5f , 0.0f, 0.0f, 1.0f, 1.0f ),
    Vertex( 0.5f,  0.5f, -0.5f , 0.0f, 0.0f, 1.0f, 1.0f ),
    Vertex( 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f ),
    Vertex(-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f ),
    Vertex( 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f ),
    Vertex(-0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f ),
    Vertex( 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f ),
    Vertex(-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f ),
    Vertex(-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f ),
    Vertex( 0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f ),
    Vertex( 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f ), 
};

WORD indexList[]
{
     0,  1,  2,     3,  2,  1,
     4,  5,  6,     7,  6,  5,
     8,  9, 10,    11, 10,  9,
    12, 13, 14,    15, 14, 13,
    16, 17, 18,    19, 18, 17,
    20, 21, 22,    23, 22, 21,
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
    auto data = VertexData();
    data.vertex = vertexList;
    data.indexes = indexList;
    data.size = 24;
    data.indexSize = 36;
	mesh = gameLibrary->CreateMeshRenderer( &data );
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