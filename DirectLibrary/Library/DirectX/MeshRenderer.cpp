#include "DirectX.h"

char* MeshRenderer::vsData = nullptr;
char* MeshRenderer::psData = nullptr;
ID3D11VertexShader* MeshRenderer::vsShader = nullptr;
ID3D11PixelShader* MeshRenderer::psShader = nullptr;
ID3D11InputLayout* MeshRenderer::inputLayout = nullptr;

D3D11_INPUT_ELEMENT_DESC inputLayoutData[]{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,	 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};


bool MeshRenderer::Init()
{
	auto device = DirectX::device;

	FILE* fp = nullptr;
	fopen_s(&fp, "Shader/vsShader.cso", "rb");
	if (fp == nullptr)
	{
		return false;	//シェーダ読み込めなかった
	}

	//ファイルの長さを取得する
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);

	//ファイルの読み込み位置を先頭に戻す
	fseek(fp, 0, SEEK_SET);

	//バイト配列をファイルの長さで作成する
	vsData = new char[size];

	//配列に読み込んだデータを入れる
	fread_s(vsData, size, size, 1, fp);

	//読み込んだファイルをクローズする
	fclose(fp);

	fp = nullptr;
	fopen_s(&fp, "Shader/psShader.cso", "rb");

	if (fp == nullptr)
	{
		return false;	//シェーダ読み込めなかった
	}

	//ファイルの長さを取得する
	fseek(fp, 0, SEEK_END);
	int size2 = ftell(fp);

	//ファイルの読み込み位置を先頭に戻す
	fseek(fp, 0, SEEK_SET);

	//バイト配列をファイルの長さで作成する
	psData = new char[size2];

	//配列に読み込んだデータを入れる
	fread_s(psData, size2, size2, 1, fp);

	//読み込んだファイルをクローズする
	fclose(fp);

	//頂点シェーダを作成する
	if (FAILED(device->CreateVertexShader(vsData, size, nullptr, &vsShader)))
	{
		return false;
	}

	//ピクセルシェーダを作成する
	if (FAILED(device->CreatePixelShader(psData, size2, nullptr, &psShader)))
	{
		return false;
	}


	//入力レイアウトを作成する
	if (FAILED(device->CreateInputLayout(inputLayoutData,
		ARRAYSIZE(inputLayoutData),
		vsData,
		size,
		&inputLayout)))
	{
		return false;
	}


	return true;
}

void MeshRenderer::Release()
{
	if (vsShader != nullptr) vsShader->Release();
	if (psShader != nullptr) psShader->Release();

	if (vsData != nullptr) delete vsData;
	if (psData != nullptr) delete psData;
}

MeshRenderer::MeshRenderer(Vertex* vertex, int size)
{
	this->vertex = vertex;
	this->size = size;

	//頂点バッファの作成に必要な構造体を作成する
	D3D11_BUFFER_DESC buffer_desc;
	buffer_desc.ByteWidth = sizeof(Vertex) * size;
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;
	buffer_desc.StructureByteStride = sizeof(Vertex);

	//頂点バッファの作成に必要な構造体を作成するその２
	D3D11_SUBRESOURCE_DATA init_data;
	init_data.pSysMem = vertex;
	init_data.SysMemPitch = 0;
	init_data.SysMemSlicePitch = 0;

	//頂点バッファを作成する
	if (FAILED(DirectX::device->CreateBuffer(&buffer_desc, &init_data, &vertexBuffer)))
	{
		return;
	}

}

MeshRenderer::~MeshRenderer()
{
	vertex = nullptr;
	if (vertexBuffer != nullptr) vertexBuffer->Release();
}

bool MeshRenderer::SetData( VertexData* data)
{
	//頂点バッファの作成に必要な構造体を作成する
	D3D11_BUFFER_DESC buffer_desc;
	buffer_desc.ByteWidth = sizeof(Vertex) * data->size;
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;
	buffer_desc.StructureByteStride = sizeof(Vertex);

	//頂点バッファの作成に必要な構造体を作成するその２
	D3D11_SUBRESOURCE_DATA init_data;
	init_data.pSysMem = data->vertex;
	init_data.SysMemPitch = 0;
	init_data.SysMemSlicePitch = 0;

	//頂点バッファを作成する
	if (FAILED(DirectX::device->CreateBuffer(&buffer_desc, &init_data, &vertexBuffer)))
	{
		return false;
	}


	//頂点バッファを更新する
	vertex = data->vertex;
	size = data->size;

	return true;
}

bool MeshRenderer::SetData(Vertex* vertex, int size)
{
	//頂点バッファを更新する
	this->vertex = vertex;
	this->size = size;

	return true;
}

void MeshRenderer::Draw()
{
	UINT strides = sizeof(Vertex);
	UINT offset = 0;
	
	//頂点データを更新する
	DirectX::context->UpdateSubresource(vertexBuffer, 0, NULL, vertex, 0, 0);

	//頂点データを書き込む
	DirectX::context->IASetVertexBuffers(0, 1, &vertexBuffer, &strides, &offset);

	//入力レイアウトを設定する
	DirectX::context->IASetInputLayout(inputLayout);

	//プリミティブを設定する
	DirectX::context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//頂点シェーダーを設定する
	DirectX::context->VSSetShader(vsShader, NULL, 0);

	//ピクセルシェーダーを設定する
	DirectX::context->PSSetShader(psShader, NULL, 0);

	//描画する
	DirectX::context->Draw(size, 0);
}
