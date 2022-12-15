#pragma once
#include <d3d11.h>	//DirectX11をインクルードする

struct Vertex
{
public:
	float pos[3];
	float color[4];
};

//DirectX11を使うクラス
class DirectX
{
private:
	static ID3D11Device* device;			//デバイス
	static ID3D11DeviceContext* context;	//コンテキスト
	static IDXGISwapChain* swapChain;		//スワップチェイン
	static ID3D11RenderTargetView* renderTargetView;	//レンダーターゲットビュー
	static ID3D11Texture2D* texture;					//レンダーテクスチャー
	static ID3D11DepthStencilView* depthStencilView;	//デプスステンシルビュー

	//シェーダ
	static ID3D11VertexShader* vsShader;	//頂点シェーダ
	static ID3D11PixelShader* psShader;		//ピクセルシェーダ
	static char* vsData;	//頂点シェーダのバイトデータ
	static char* psData;	//ピクセルシェーダのバイトデータ
	static ID3D11Buffer* vertexBuffer;
	static ID3D11InputLayout* inputLayout;

	//スワップチェイン作成用の構造体を作成する
	static void CreateSwapChainDesc( HWND window_handle, DXGI_SWAP_CHAIN_DESC* dxgi);

	//デバイスとスワップチェインを作成する
	static bool CreateDeviceAndSwapChain( HWND window_handle );

	//レンダーターゲットビューを作成する
	static bool CreateRenderTargetView();

	//デプスステンシルを作成する
	static bool CreateDepthStencilView( HWND window_handle );

	//シェーダを作成する
	static bool CreateShader();

public:
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
