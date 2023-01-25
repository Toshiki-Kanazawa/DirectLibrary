#pragma once
#include "../IMeshRenderer.h"
#include "DirectXMath.h"
using namespace DirectX;

struct ConstantBuffer
{
	XMFLOAT4X4 world;
	XMFLOAT4X4 view;
	XMFLOAT4X4 projection;
};

//DirectX�̋@�\���g���Ď�������N���X
class MeshRenderer : public IMeshRenderer
{
private:
	//�V�F�[�_
	static ID3D11VertexShader* vsShader;	//���_�V�F�[�_
	static ID3D11PixelShader* psShader;		//�s�N�Z���V�F�[�_
	static char* vsData;	//���_�V�F�[�_�̃o�C�g�f�[�^
	static char* psData;	//�s�N�Z���V�F�[�_�̃o�C�g�f�[�^
	static ID3D11InputLayout* inputLayout;	//�C���v�b�g���C�A�E�g

	static ID3D11Buffer* constantBuffer;	//�R���X�^���g�o�b�t�@�[

	ID3D11Buffer* vertexBuffer;	//���_�o�b�t�@�[
	ID3D11Buffer* indexBuffer;	//�C���f�b�N�X�o�b�t�@�[
	Vertex* vertex;
	UINT size;

	bool CreateVertexBuffer( const Vertex& vertexes, int size );
	bool CreateIndexBuffer( const WORD& indexes, int size );

public:
	static bool Init();
	static void Release();

	MeshRenderer( VertexData* data );
	~MeshRenderer();
	//bool SetData( VertexData* data) override;
	//void SetContextBuffer(const GameObject& gameObject, const Camera& camera );
	void Draw() override;
	void SetData(const GameObject& gameObject);
};