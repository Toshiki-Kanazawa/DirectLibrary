#pragma once
#include "../GameLibrary.h"
#include <d3d11.h>	//DirectX11をインクルードする
#include "InputManager.h"
#include "MeshRenderer.h"
#include <Windows.h>
#include <stdio.h>


//DirectX11を使うクラス
class DirectX11 : public GameLibrary
{
public:
	static ID3D11Device* device;			//デバイス
	static ID3D11DeviceContext* context;	//コンテキスト
	static IDXGISwapChain* swapChain;		//スワップチェイン
	static ID3D11RenderTargetView* renderTargetView;	//レンダーターゲットビュー
	static ID3D11Texture2D* texture;					//レンダーテクスチャー
	static ID3D11DepthStencilView* depthStencilView;	//デプスステンシルビュー
	static D3D11_VIEWPORT viewPort;

	//スワップチェイン作成用の構造体を作成する
	static void CreateSwapChainDesc( HWND window_handle, DXGI_SWAP_CHAIN_DESC* dxgi);

	//デバイスとスワップチェインを作成する
	static bool CreateDeviceAndSwapChain( HWND window_handle );

	//レンダーターゲットビューを作成する
	static bool CreateRenderTargetView();

	//デプスステンシルを作成する
	static bool CreateDepthStencilView( HWND window_handle );

	static float clear_color[4];

//public:
	//初期化関数
	bool Init( HWND window_handle ) override;

	//解放関数
	void Release() override;

	//描画を開始する関数(画面を単色でクリアする)
	void StartRendering() override;

	//描画を終了する関数(画面に描画を反映する)
	void FinishRendering() override;

	//MeshRendererを生成する
	IMeshRenderer* CreateMeshRenderer( VertexData* data ) override;

	//static ID3D11Device* GetDevice() { return device; }
	//static ID3D11DeviceContext* GetDeviceContext() { return context; }
	//static ID3D11RenderTargetView* GetRenderTargetView() { return renderTargetView; }
	//static ID3D11DepthStencilView* GetDepthStencilView() { return depthStencilView; }

	void SetClearColor(float r, float g, float b, float a) override;
	void UpdateCamera(const Camera& camera) override;

};
