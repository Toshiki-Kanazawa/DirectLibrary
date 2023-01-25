#pragma once
#include <string>
#include "../Library/GameLibrary.h"

class ModelObject
{
private:
	VertexData* vertexData;	//���_�f�[�^
	IMeshRenderer* mesh;	//���b�V��
public:
	static GameLibrary* gameLib;

	ModelObject(const std::wstring& filePath);
	~ModelObject();

	//���W�ϐ�
	float posX;
	float posY;
	float posZ;

	//��]�ϐ�
	float rotX;
	float rotY;
	float rotZ;

	//�g�嗦�ϐ�
	float scaleX;
	float scaleY;
	float scaleZ;

	//���f����`�悷��֐�
	void Render();
};