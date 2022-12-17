#include <stdio.h>
#include "DirectX.h"
#include <Windows.h>

#pragma comment(lib,"d3d11.lib")

ID3D11Device* DirectX::device = nullptr;			//デバイス
ID3D11DeviceContext* DirectX::context = nullptr;	//コンテキスト
IDXGISwapChain* DirectX::swapChain = nullptr;		//スワップチェイン
ID3D11RenderTargetView* DirectX::renderTargetView = nullptr;	//レンダーターゲットビュー
ID3D11Texture2D* DirectX::texture = nullptr;					//レンダーテクスチャー
ID3D11DepthStencilView* DirectX::depthStencilView = nullptr;	//デプスステンシルビュー
char* DirectX::vsData = nullptr;
char* DirectX::psData = nullptr;
ID3D11VertexShader* DirectX::vsShader = nullptr;
ID3D11PixelShader* DirectX::psShader = nullptr;
ID3D11InputLayout* DirectX::inputLayout = nullptr;
ID3D11Buffer* DirectX::vertexBuffer = nullptr;

Vertex vertexList[]
{
   { { -0.2f,  0.2f, 0.2f }, { 1.0f, 1.0f, 1.0f, 1.0f } },
	{ {  0.2f, -0.2f, 0.2f }, { 1.0f, 1.0f, 1.0f, 1.0f } },
	{ { -0.2f, -0.2f, 0.2f }, { 1.0f, 1.0f, 1.0f, 1.0f } },
};

D3D11_INPUT_ELEMENT_DESC inputLayoutData[]{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,	 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

//スワップチェインを生成するときに必要なパラメータを用意する
void DirectX::CreateSwapChainDesc( HWND window_handle, DXGI_SWAP_CHAIN_DESC* dxgi)
{
	RECT rect;
	GetClientRect(window_handle, &rect);

	ZeroMemory(dxgi, sizeof(DXGI_SWAP_CHAIN_DESC));
	dxgi->BufferCount = 1;
	dxgi->BufferDesc.Width = (rect.right) - (rect.left);
	dxgi->BufferDesc.Height = (rect.bottom) - (rect.top);
	dxgi->BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	dxgi->BufferDesc.RefreshRate.Numerator = 60;
	dxgi->BufferDesc.RefreshRate.Denominator = 1;
	dxgi->BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	dxgi->OutputWindow = window_handle;
	dxgi->SampleDesc.Count = 1;
	dxgi->SampleDesc.Quality = 0;
	dxgi->Windowed = true;
}

//デバイスとスワップチェインとコンテキストを作成する
bool DirectX::CreateDeviceAndSwapChain(HWND window_handle)
{
	DXGI_SWAP_CHAIN_DESC dxgi;
	CreateSwapChainDesc( window_handle, &dxgi);
	D3D_FEATURE_LEVEL level;
	if (FAILED(D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&dxgi,
		&swapChain,
		&device,
		&level,
		&context
	)
	))
	{
		return false;
	}
	return true;
}

//レンダーターゲットビューの作成
bool DirectX::CreateRenderTargetView()
{
	ID3D11Texture2D* back_buffer;
	if (FAILED(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer)))
	{
		return false;
	}

	if (FAILED(device->CreateRenderTargetView(back_buffer, nullptr, &renderTargetView)))
	{
		return false;
	}

	back_buffer->Release();

	return true;
}

//デプスステンシルビューの作成
bool DirectX::CreateDepthStencilView(HWND window_handle)
{
	RECT rect;
	GetClientRect(window_handle, &rect);

	D3D11_TEXTURE2D_DESC texture_desc;
	ZeroMemory(&texture_desc, sizeof(D3D11_TEXTURE2D_DESC));
	texture_desc.Width = (rect.right) - (rect.left);
	texture_desc.Height = (rect.bottom) - (rect.top);
	texture_desc.MipLevels = 1;
	texture_desc.ArraySize = 1;
	texture_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	texture_desc.SampleDesc.Count = 1;
	texture_desc.SampleDesc.Quality = 0;
	texture_desc.Usage = D3D11_USAGE_DEFAULT;
	texture_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	texture_desc.CPUAccessFlags = 0;
	texture_desc.MiscFlags = 0;

	if (FAILED(device->CreateTexture2D(&texture_desc, NULL, &texture)))
	{
		return false;
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC dsv_desc;
	ZeroMemory(&dsv_desc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	dsv_desc.Format = texture_desc.Format;
	dsv_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsv_desc.Texture2D.MipSlice = 0;
	if (FAILED(device->CreateDepthStencilView(texture, &dsv_desc, &depthStencilView)))
	{
		return false;
	}

	return true;
}

bool DirectX::CreateShader()
{
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

	//頂点バッファの作成に必要な構造体を作成する
	D3D11_BUFFER_DESC buffer_desc;
	buffer_desc.ByteWidth = sizeof(Vertex) * 3;
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;
	buffer_desc.StructureByteStride = sizeof(Vertex);

	//頂点バッファの作成に必要な構造体を作成するその２
	D3D11_SUBRESOURCE_DATA init_data;
	init_data.pSysMem = vertexList;
	init_data.SysMemPitch = 0;
	init_data.SysMemSlicePitch = 0;

	//頂点バッファを作成する
	if (FAILED(device->CreateBuffer(&buffer_desc, &init_data, &vertexBuffer)))
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

//DirectXの初期化処理
bool DirectX::Init()
{
	HWND window_handle = FindWindow(L"DirectLibrary", nullptr);

	//デバイスとコンテキストとスワップチェインの作成
	if (!CreateDeviceAndSwapChain(window_handle))
	{
		return false;
	}

	//レンダーターゲットの作成
	if (!CreateRenderTargetView())
	{
		return false;
	}

	//デプスステンシルの作成
	if (!CreateDepthStencilView(window_handle))
	{
		return false;
	}

	//TODO::ビューポートの設定
	RECT rect;
	GetClientRect(window_handle, &rect);

	//ビューポートの設定
	D3D11_VIEWPORT view_port;
	view_port.TopLeftX = 0;							// 左上X座標
	view_port.TopLeftY = 0;							// 左上Y座標
	view_port.Width = (rect.right - rect.left);		// 横幅
	view_port.Height = (rect.bottom - rect.top);	// 縦幅
	view_port.MinDepth = 0.0f;						// 最小深度
	view_port.MaxDepth = 1.0f;						// 最大深度

	context->RSSetViewports(
		1,					// 設定するビューポートの数
		&view_port);		// 設定するビューポート情報のポインタ
	//シェーダーの作成
	if (!CreateShader())
	{
		return false;
	}

	return true;
}

//DirectXの解放関数
void DirectX::Release()
{
	if (vsShader != nullptr) vsShader->Release();
	if (psShader != nullptr) psShader->Release();

	if (vsData != nullptr) delete vsData;
	if (psData != nullptr) delete psData;

	if (depthStencilView != nullptr) depthStencilView->Release();
	if (texture != nullptr) texture->Release();
	if (renderTargetView != nullptr) renderTargetView->Release();
	if (swapChain != nullptr) swapChain->Release();
	if (context != nullptr) context->Release();
	if (device != nullptr) device->Release();
}

//描画開始関数
void DirectX::StartRendering()
{
	float clear_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

	InputManager::Update();

	if (InputManager::Trg(KeyType::A))
	{
		vertexList[0].pos[1] = 1.0f;

		clear_color[0] = 1.0f;
	}
	if (InputManager::Rel(KeyType::Space))
	{
		clear_color[1] = 1.0f;
	}
	if (InputManager::On(KeyType::_2))
	{
		vertexList[0].pos[1] = 1.0f;
		clear_color[2] = 1.0f;
	}

	context->ClearRenderTargetView(renderTargetView, clear_color);
	context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

//描画終了関数
void DirectX::FinishRendering()
{
	swapChain->Present(0, 0);
}

//ポリゴンを描画する関数
void DirectX::RenderingPolygon()
{
	UINT strides = sizeof(Vertex);
	UINT offset = 0;

	context->UpdateSubresource(vertexBuffer, 0, NULL, &vertexList, 0, 0);
	context->IASetVertexBuffers(0, 1, &vertexBuffer, &strides, &offset );
	context->IASetInputLayout(inputLayout);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->VSSetShader(vsShader, NULL, 0);
	context->PSSetShader(psShader, NULL, 0);
	context->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	context->Draw(3, 0);
}