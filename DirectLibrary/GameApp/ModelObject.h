#pragma once
#include <string>

class ModelObject
{
private:
	IMeshRenderer* mesh;	//���b�V��
public:
	static Camera* camera;	//�J����

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