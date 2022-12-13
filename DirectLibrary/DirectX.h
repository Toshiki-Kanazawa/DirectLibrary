#pragma once
#include <d3d11.h>	//DirectX11���C���N���[�h����

//DirectX11���g���N���X
class DirectX
{
private:
	static ID3D11Device* device;			//�f�o�C�X
	static ID3D11DeviceContext* context;	//�R���e�L�X�g
	static IDXGISwapChain* swapChain;		//�X���b�v�`�F�C��
	static ID3D11RenderTargetView* renderTargetView;	//�����_�[�^�[�Q�b�g�r���[
	static ID3D11Texture2D* texture;					//�����_�[�e�N�X�`���[
	static ID3D11DepthStencilView* depthStencilView;	//�f�v�X�X�e���V���r���[

	//�X���b�v�`�F�C���쐬�p�̍\���̂��쐬����
	static void CreateSwapChainDesc( HWND window_handle, DXGI_SWAP_CHAIN_DESC* dxgi);

	//�f�o�C�X�ƃX���b�v�`�F�C�����쐬����
	static bool CreateDeviceAndSwapChain( HWND window_handle );

	//�����_�[�^�[�Q�b�g�r���[���쐬����
	static bool CreateRenderTargetView();

	//�f�v�X�X�e���V�����쐬����
	static bool CreateDepthStencilView( HWND window_handle );

public:
	//�������֐�
	static bool Init();

	//����֐�
	static void Release();

	//�`����J�n����֐�(��ʂ�P�F�ŃN���A����)
	static void StartRendering();

	//�`����I������֐�(��ʂɕ`��𔽉f����)
	static void FinishRendering();

	//�|���S����`�悷��
	static void RenderingPolygon();

};
