#pragma once
#include <d3d11.h>	//DirectX11���C���N���[�h����

//DirectX11���g���N���X
class DirectX
{
public:
	static ID3D11Device* device;			//�f�o�C�X
	static ID3D11DeviceContext* context;	//�R���e�L�X�g
	static IDXGISwapChain* swapChain;		//�X���b�v�`�F�C��

	static ID3D11RenderTargetView* renderTargetView;	//�����_�[�^�[�Q�b�g�r���[
	static ID3D11Texture2D* texture;					//�����_�[�e�N�X�`���[
	static ID3D11DepthStencilView* depthStencilView;	//�f�v�X�X�e���V���r���[

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
