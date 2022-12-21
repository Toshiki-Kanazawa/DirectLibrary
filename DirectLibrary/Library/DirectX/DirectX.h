#pragma once
#include "../GameLibrary.h"
#include <d3d11.h>	//DirectX11���C���N���[�h����
#include "InputManager.h"
#include "MeshRenderer.h"
#include <Windows.h>
#include <stdio.h>


//DirectX11���g���N���X
class DirectX11 : public GameLibrary
{
public:
	static ID3D11Device* device;			//�f�o�C�X
	static ID3D11DeviceContext* context;	//�R���e�L�X�g
	static IDXGISwapChain* swapChain;		//�X���b�v�`�F�C��
	static ID3D11RenderTargetView* renderTargetView;	//�����_�[�^�[�Q�b�g�r���[
	static ID3D11Texture2D* texture;					//�����_�[�e�N�X�`���[
	static ID3D11DepthStencilView* depthStencilView;	//�f�v�X�X�e���V���r���[
	static D3D11_VIEWPORT viewPort;

	//�X���b�v�`�F�C���쐬�p�̍\���̂��쐬����
	static void CreateSwapChainDesc( HWND window_handle, DXGI_SWAP_CHAIN_DESC* dxgi);

	//�f�o�C�X�ƃX���b�v�`�F�C�����쐬����
	static bool CreateDeviceAndSwapChain( HWND window_handle );

	//�����_�[�^�[�Q�b�g�r���[���쐬����
	static bool CreateRenderTargetView();

	//�f�v�X�X�e���V�����쐬����
	static bool CreateDepthStencilView( HWND window_handle );

	static float clear_color[4];

//public:
	//�������֐�
	bool Init( HWND window_handle ) override;

	//����֐�
	void Release() override;

	//�`����J�n����֐�(��ʂ�P�F�ŃN���A����)
	void StartRendering() override;

	//�`����I������֐�(��ʂɕ`��𔽉f����)
	void FinishRendering() override;

	//MeshRenderer�𐶐�����
	IMeshRenderer* CreateMeshRenderer( VertexData* data ) override;

	//static ID3D11Device* GetDevice() { return device; }
	//static ID3D11DeviceContext* GetDeviceContext() { return context; }
	//static ID3D11RenderTargetView* GetRenderTargetView() { return renderTargetView; }
	//static ID3D11DepthStencilView* GetDepthStencilView() { return depthStencilView; }

	void SetClearColor(float r, float g, float b, float a) override;
	void UpdateCamera(const Camera& camera) override;

};
