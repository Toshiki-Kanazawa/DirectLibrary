#pragma once
#include <string>
#include "../Library/GameLibrary.h"

class ModelObject
{
private:
	VertexData* vertexData;	//頂点データ
	IMeshRenderer* mesh;	//メッシュ
public:
	static GameLibrary* gameLib;
	static Camera* camera;	//カメラ

	ModelObject(const std::wstring& filePath);
	~ModelObject();

	//座標変数
	float posX;
	float posY;
	float posZ;

	//回転変数
	float rotX;
	float rotY;
	float rotZ;

	//拡大率変数
	float scaleX;
	float scaleY;
	float scaleZ;

	//モデルを描画する関数
	void Render();
};