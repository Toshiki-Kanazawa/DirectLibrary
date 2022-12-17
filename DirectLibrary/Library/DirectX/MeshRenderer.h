#pragma once
#include "../IMeshRenderer.h"

//DirectX�̋@�\���g���Ď�������N���X
class MeshRenderer : public IMeshRenderer
{
private:
	//�V�F�[�_
	static ID3D11VertexShader* vsShader;	//���_�V�F�[�_
	static ID3D11PixelShader* psShader;		//�s�N�Z���V�F�[�_
	static char* vsData;	//���_�V�F�[�_�̃o�C�g�f�[�^
	static char* psData;	//�s�N�Z���V�F�[�_�̃o�C�g�f�[�^
	static ID3D11InputLayout* inputLayout;

	ID3D11Buffer* vertexBuffer;
	Vertex* vertex;
	UINT size;

public:
	static bool Init();
	static void Release();

	MeshRenderer( Vertex* vertex, int size );
	~MeshRenderer();
	bool SetData( VertexData* data) override;
	bool SetData(Vertex* vertex, int size) override;
	void Draw() override;
};