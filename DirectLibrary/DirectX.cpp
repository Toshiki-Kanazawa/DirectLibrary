#include "DirectX.h"
#include <Windows.h>

#pragma comment(lib,"d3d11.lib")

ID3D11Device* DirectX::device = nullptr;			//�f�o�C�X
ID3D11DeviceContext* DirectX::context = nullptr;	//�R���e�L�X�g
IDXGISwapChain* DirectX::swapChain = nullptr;		//�X���b�v�`�F�C��
ID3D11RenderTargetView* DirectX::renderTargetView = nullptr;	//�����_�[�^�[�Q�b�g�r���[
ID3D11Texture2D* DirectX::texture = nullptr;					//�����_�[�e�N�X�`���[
ID3D11DepthStencilView* DirectX::depthStencilView = nullptr;	//�f�v�X�X�e���V���r���[


//�X���b�v�`�F�C���𐶐�����Ƃ��ɕK�v�ȃp�����[�^��p�ӂ���
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

//�f�o�C�X�ƃX���b�v�`�F�C���ƃR���e�L�X�g���쐬����
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
	//�f�o�C�X�ƃR���e�L�X�g�ƃX���b�v�`�F�C���̍쐬
	CreateDeviceAndSwapChain( swapChain, device, context);

	//TODO::�����_�[�^�[�Q�b�g�̍쐬

	//TODO::�r���[�|�[�g�̐ݒ�

	//TODO::�V�F�[�_�[�̍쐬

	return true;
}

//DirectX�̉���֐�
void DirectX::Release()
{

}

//�`��J�n�֐�
void DirectX::StartRendering()
{

}

//�`��I���֐�
void DirectX::FinishRendering()
{

}

//�|���S����`�悷��֐�
void DirectX::RenderingPolygon()
{

}