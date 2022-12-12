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
void SetupDxgiSwapChainDesc(DXGI_SWAP_CHAIN_DESC* dxgi)
{
	HWND window_handle = FindWindow(L"DirectLibrary", nullptr);
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
void CreateDeviceAndSwapChain( IDXGISwapChain* swapChain, ID3D11Device* device, ID3D11DeviceContext* context )
{
	DXGI_SWAP_CHAIN_DESC dxgi;
	SetupDxgiSwapChainDesc(&dxgi);
	D3D_FEATURE_LEVEL level;

	D3D11CreateDeviceAndSwapChain
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
	);
}

bool DirectX::Init()
{
	//デバイスとコンテキストとスワップチェインの作成
	CreateDeviceAndSwapChain( swapChain, device, context);

	//TODO::レンダーターゲットの作成

	//TODO::ビューポートの設定

	//TODO::シェーダーの作成

	return true;
}

//DirectXの解放関数
void DirectX::Release()
{

}

//描画開始関数
void DirectX::StartRendering()
{

}

//描画終了関数
void DirectX::FinishRendering()
{

}

//ポリゴンを描画する関数
void DirectX::RenderingPolygon()
{

}