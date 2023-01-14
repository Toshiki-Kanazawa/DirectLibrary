#pragma once
#include "../Library/GameLibrary.h"

class IScene
{
public:
	virtual void Update( float deltaTime ) = 0;
	virtual void Render() = 0;
};

class TestScene : public IScene
{
private:
	IMeshRenderer* mesh;
	IMeshRenderer* mesh2;
public:
	TestScene( GameLibrary* gameLibrary );
	~TestScene();
	void Update(float deltaTime) override;
	void Render() override;
};

class GameApp
{
private:
	GameLibrary* gameLibrary;
	IScene* scene;
	static Camera camera;
public:
	GameApp(GameLibrary* gameLibrary);
	void Update();
	void Render();
	static const Camera& GetCamera(){ return camera; }
};