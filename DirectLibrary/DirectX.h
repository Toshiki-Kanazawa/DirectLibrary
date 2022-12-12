#pragma once
#include <d3d11.h>	//DirectX11をインクルードする

//DirectX11を使うクラス
class DirectX
{
public:
	static ID3D11Device* device;			//デバイス
	static ID3D11DeviceContext* context;	//コンテキスト
	static IDXGISwapChain* swapChain;		//スワップチェイン

	static ID3D11RenderTargetView* renderTargetView;	//レンダーターゲットビュー
	static ID3D11Texture2D* texture;					//レンダーテクスチャー
	static ID3D11DepthStencilView* depthStencilView;	//デプスステンシルビュー

	//初期化関数
	static bool Init();

	//解放関数
	static void Release();

	//描画を開始する関数(画面を単色でクリアする)
	static void StartRendering();

	//描画を終了する関数(画面に描画を反映する)
	static void FinishRendering();

	//ポリゴンを描画する
	static void RenderingPolygon();

};
