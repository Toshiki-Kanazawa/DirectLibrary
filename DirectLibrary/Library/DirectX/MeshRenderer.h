#pragma once
#include "../IMeshRenderer.h"

//DirectXの機能を使って実装するクラス
class MeshRenderer : public IMeshRenderer
{
private:
	//シェーダ
	static ID3D11VertexShader* vsShader;	//頂点シェーダ
	static ID3D11PixelShader* psShader;		//ピクセルシェーダ
	static char* vsData;	//頂点シェーダのバイトデータ
	static char* psData;	//ピクセルシェーダのバイトデータ
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