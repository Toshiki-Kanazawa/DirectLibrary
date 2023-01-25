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

//DirectXの機能を使って実装するクラス
class MeshRenderer : public IMeshRenderer
{
private:
	//シェーダ
	static ID3D11VertexShader* vsShader;	//頂点シェーダ
	static ID3D11PixelShader* psShader;		//ピクセルシェーダ
	static char* vsData;	//頂点シェーダのバイトデータ
	static char* psData;	//ピクセルシェーダのバイトデータ
	static ID3D11InputLayout* inputLayout;	//インプットレイアウト

	static ID3D11Buffer* constantBuffer;	//コンスタントバッファー

	ID3D11Buffer* vertexBuffer;	//頂点バッファー
	ID3D11Buffer* indexBuffer;	//インデックスバッファー
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