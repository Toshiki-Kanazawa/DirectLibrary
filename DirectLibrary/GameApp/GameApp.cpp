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
	//•`‰æ‚ÌŠJŽn
	gameLibrary->StartRendering();

	//ƒV[ƒ“‚Ì•`‰æ
	scene->Render();

	//•`‰æ‚ÌI—¹(‰æ–Ê‚Ö”½‰f‚·‚é)
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
	//‚±‚±‚ÅŽOŠpŒ`‚ð•`‰æ‚µ‚½‚¢
	mesh->Draw();
}