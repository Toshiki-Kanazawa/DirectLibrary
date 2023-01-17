#pragma once
#include <string>

class ModelObject
{
public:
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