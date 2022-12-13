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

	//TODO::シェーダーの作成

	return true;
}

//DirectXの解放関数
void DirectX::Release()
{
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
	float clear_color[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
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

}