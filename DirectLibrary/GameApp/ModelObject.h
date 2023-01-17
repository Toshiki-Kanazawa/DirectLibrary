#pragma once
#include <string>

class ModelObject
{
private:
	IMeshRenderer* mesh;	//メッシュ
public:
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