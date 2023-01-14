#include "DirectX.h"

char* MeshRenderer::vsData = nullptr;
char* MeshRenderer::psData = nullptr;
ID3D11VertexShader* MeshRenderer::vsShader = nullptr;
ID3D11PixelShader* MeshRenderer::psShader = nullptr;
ID3D11InputLayout* MeshRenderer::inputLayout = nullptr;
ID3D11Buffer* MeshRenderer::constantBuffer = nullptr;

D3D11_INPUT_ELEMENT_DESC inputLayoutData[]{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,	 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};


bool MeshRenderer::Init()
{
	auto device = DirectX11::device;

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


	//コンスタントバッファーを作成する
	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = sizeof(ConstantBuffer);
	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	if (FAILED(device->CreateBuffer(&cbDesc, NULL, &constantBuffer)))
	{
		return false;
	}
	return true;
}

void MeshRenderer::UpdateCamera(const Camera& camera)
{
	//ワールド座標は固定値
	XMMATRIX worldMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	XMVECTOR eye = XMVectorSet(camera.posX, camera.posY, camera.posZ, 0.0f);	//カメラの座標
	XMVECTOR focus = XMVectorSet(camera.focusX, camera.focusY, camera.focusZ, 0.0f);	//カメラが見ている座標
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);		//カメラの上向きのベクトル
	XMMATRIX viewMatrix = XMMatrixLookAtLH(eye, focus, up);

	float    fov = XMConvertToRadians(45.0f);
	float    aspect = DirectX11::viewPort.Width / DirectX11::viewPort.Height;
	float    nearZ = 0.1f;
	float    farZ = 100.0f;
	XMMATRIX projMatrix = XMMatrixPerspectiveFovLH(fov, aspect, nearZ, farZ);


	//コンスタントバッファーを更新する
	ConstantBuffer cb;
	XMStoreFloat4x4(&cb.world, XMMatrixTranspose(worldMatrix));
	XMStoreFloat4x4(&cb.view, XMMatrixTranspose(viewMatrix));
	XMStoreFloat4x4(&cb.projection, XMMatrixTranspose(projMatrix));
	DirectX11::context->UpdateSubresource(constantBuffer, 0, NULL, &cb, 0, 0);

}

void MeshRenderer::Release()
{
	if (vsShader != nullptr) vsShader->Release();
	if (psShader != nullptr) psShader->Release();

	if (vsData != nullptr) delete vsData;
	if (psData != nullptr) delete psData;
}

MeshRenderer::MeshRenderer(VertexData* data )
{
	//this->vertex = vertex;
	SetData(data);

	////頂点バッファの作成に必要な構造体を作成する
	//D3D11_BUFFER_DESC buffer_desc;
	//buffer_desc.ByteWidth = sizeof(Vertex) * size;
	//buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	//buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//buffer_desc.CPUAccessFlags = 0;
	//buffer_desc.MiscFlags = 0;
	//buffer_desc.StructureByteStride = sizeof(Vertex);

	////頂点バッファの作成に必要な構造体を作成するその２
	//D3D11_SUBRESOURCE_DATA init_data;
	//init_data.pSysMem = vertex;
	//init_data.SysMemPitch = 0;
	//init_data.SysMemSlicePitch = 0;

	////頂点バッファを作成する
	//if (FAILED(DirectX::device->CreateBuffer(&buffer_desc, &init_data, &vertexBuffer)))
	//{
	//	return;
	//}

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
	if (FAILED(DirectX11::device->CreateBuffer(&buffer_desc, &init_data, &vertexBuffer)))
	{
		return false;
	}

	//インデックスバッファーの作成に必要な構造体を作成する
	D3D11_BUFFER_DESC index_desc;
	index_desc.ByteWidth = sizeof(WORD) * data->indexSize;
	index_desc.Usage = D3D11_USAGE_DEFAULT;
	index_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	index_desc.CPUAccessFlags = 0;
	index_desc.MiscFlags = 0;
	index_desc.StructureByteStride = 0;

	//インデックスバッファーの作成に必要な構造体を作成する2
	D3D11_SUBRESOURCE_DATA init_data2;
	init_data2.pSysMem = data->indexes;
	init_data2.SysMemPitch = 0;
	init_data2.SysMemSlicePitch = 0;

	//インデックスバッファーを作成する
	if (FAILED(DirectX11::device->CreateBuffer(&index_desc, &init_data2, &indexBuffer)))
	{
		return false;
	}

	//頂点バッファを更新する
	//vertex = data->vertex;
	//size = data->size;

	size = data->indexSize;

	//頂点データを更新する
	DirectX11::context->UpdateSubresource(vertexBuffer, 0, NULL, data->vertex, 0, 0);

	return true;
}

//bool MeshRenderer::SetData(Vertex* vertex, int size)
//{
//	//頂点バッファを更新する
//	this->vertex = vertex;
//	this->size = size;
//
//	return true;
//}

void MeshRenderer::Draw()
{
	UINT strides = sizeof(Vertex);
	UINT offset = 0;
	
	//頂点データを更新する
	//DirectX::context->UpdateSubresource(vertexBuffer, 0, NULL, vertex, 0, 0);

	//頂点データを書き込む
	DirectX11::context->IASetVertexBuffers(0, 1, &vertexBuffer, &strides, &offset);

	//インデックスデータを書き込む
	DirectX11::context->IASetIndexBuffer( indexBuffer, DXGI_FORMAT_R16_UINT, 0);
	
	//コンスタントバッファーを設定する
	DirectX11::context->VSSetConstantBuffers(0, 1, &constantBuffer);

	//入力レイアウトを設定する
	DirectX11::context->IASetInputLayout(inputLayout);

	//プリミティブを設定する
	DirectX11::context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//頂点シェーダーを設定する
	DirectX11::context->VSSetShader(vsShader, NULL, 0);

	//ピクセルシェーダーを設定する
	DirectX11::context->PSSetShader(psShader, NULL, 0);

	//描画する
	//DirectX::context->Draw(size, 0);
	DirectX11::context->DrawIndexed(size, 0, 0);
}

void MeshRenderer::SetContextBuffer(const GameObject& gameObject, const Camera& camera )
{
	//ワールド座標は固定値
	XMMATRIX worldMatrix = XMMatrixTranslation(gameObject.pos.x, gameObject.pos.y, gameObject.pos.z);

	XMVECTOR eye = XMVectorSet(camera.posX, camera.posY, camera.posZ, 0.0f);	//カメラの座標
	XMVECTOR focus = XMVectorSet(camera.focusX, camera.focusY, camera.focusZ, 0.0f);	//カメラが見ている座標
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);		//カメラの上向きのベクトル
	XMMATRIX viewMatrix = XMMatrixLookAtLH(eye, focus, up);

	float    fov = XMConvertToRadians(45.0f);
	float    aspect = DirectX11::viewPort.Width / DirectX11::viewPort.Height;
	float    nearZ = 0.1f;
	float    farZ = 100.0f;
	XMMATRIX projMatrix = XMMatrixPerspectiveFovLH(fov, aspect, nearZ, farZ);


	//コンスタントバッファーを更新する
	ConstantBuffer cb;
	XMStoreFloat4x4(&cb.world, XMMatrixTranspose(worldMatrix));
	XMStoreFloat4x4(&cb.view, XMMatrixTranspose(viewMatrix));
	XMStoreFloat4x4(&cb.projection, XMMatrixTranspose(projMatrix));
	DirectX11::context->UpdateSubresource(constantBuffer, 0, NULL, &cb, 0, 0);

}
