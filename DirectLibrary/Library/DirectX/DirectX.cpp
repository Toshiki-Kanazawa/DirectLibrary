#include "DirectX.h"

#pragma comment(lib,"d3d11.lib")

ID3D11Device* DirectX11::device = nullptr;			//�f�o�C�X
ID3D11DeviceContext* DirectX11::context = nullptr;	//�R���e�L�X�g
IDXGISwapChain* DirectX11::swapChain = nullptr;		//�X���b�v�`�F�C��
ID3D11RenderTargetView* DirectX11::renderTargetView = nullptr;	//�����_�[�^�[�Q�b�g�r���[
ID3D11Texture2D* DirectX11::texture = nullptr;					//�����_�[�e�N�X�`���[
ID3D11DepthStencilView* DirectX11::depthStencilView = nullptr;	//�f�v�X�X�e���V���r���[
float DirectX11::clear_color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
D3D11_VIEWPORT DirectX11::viewPort = {};

//�X���b�v�`�F�C���𐶐�����Ƃ��ɕK�v�ȃp�����[�^��p�ӂ���
void DirectX11::CreateSwapChainDesc( HWND window_handle, DXGI_SWAP_CHAIN_DESC* dxgi)
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

//�f�o�C�X�ƃX���b�v�`�F�C���ƃR���e�L�X�g���쐬����
bool DirectX11::CreateDeviceAndSwapChain(HWND window_handle)
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

//�����_�[�^�[�Q�b�g�r���[�̍쐬
bool DirectX11::CreateRenderTargetView()
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

//�f�v�X�X�e���V���r���[�̍쐬
bool DirectX11::CreateDepthStencilView(HWND window_handle)
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

//DirectX�̏���������
bool DirectX11::Init( HWND window_handle )
{
	//�f�o�C�X�ƃR���e�L�X�g�ƃX���b�v�`�F�C���̍쐬
	if (!CreateDeviceAndSwapChain(window_handle))
	{
		return false;
	}

	//�����_�[�^�[�Q�b�g�̍쐬
	if (!CreateRenderTargetView())
	{
		return false;
	}

	//�f�v�X�X�e���V���̍쐬
	if (!CreateDepthStencilView(window_handle))
	{
		return false;
	}

	//TODO::�r���[�|�[�g�̐ݒ�
	RECT rect;
	GetClientRect(window_handle, &rect);

	//�r���[�|�[�g�̐ݒ�
	ZeroMemory(&viewPort, sizeof(D3D11_VIEWPORT));
	viewPort.TopLeftX = 0;							// ����X���W
	viewPort.TopLeftY = 0;							// ����Y���W
	viewPort.Width = (float)(rect.right - rect.left);		// ����
	viewPort.Height = (float)(rect.bottom - rect.top);	// �c��
	viewPort.MinDepth = 0.0f;						// �ŏ��[�x
	viewPort.MaxDepth = 1.0f;						// �ő�[�x

	context->RSSetViewports(
		1,					// �ݒ肷��r���[�|�[�g�̐�
		&viewPort);		// �ݒ肷��r���[�|�[�g���̃|�C���^

	MeshRenderer::Init();

	return true;
}

//DirectX�̉���֐�
void DirectX11::Release()
{
	MeshRenderer::Release();
	if (depthStencilView != nullptr) depthStencilView->Release();
	if (texture != nullptr) texture->Release();
	if (renderTargetView != nullptr) renderTargetView->Release();
	if (swapChain != nullptr) swapChain->Release();
	if (context != nullptr) context->Release();
	if (device != nullptr) device->Release();
}

//�`��J�n�֐�
void DirectX11::StartRendering()
{
	//float clear_color[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	context->ClearRenderTargetView(renderTargetView, clear_color);
	context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->OMSetRenderTargets(1, &renderTargetView, depthStencilView);
}

//�`��I���֐�
void DirectX11::FinishRendering()
{
	swapChain->Present(0, 0);
}

//�|���S����`�悷��֐�
//void DirectX::RenderingPolygon()
//{
//	UINT strides = sizeof(Vertex);
//	UINT offset = 0;
//
//	context->UpdateSubresource(vertexBuffer, 0, NULL, &vertexList, 0, 0);
//	context->IASetVertexBuffers(0, 1, &vertexBuffer, &strides, &offset );
//	context->IASetInputLayout(inputLayout);
//	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//	context->VSSetShader(vsShader, NULL, 0);
//	context->PSSetShader(psShader, NULL, 0);
//	context->OMSetRenderTargets(1, &renderTargetView, depthStencilView);
//
//	context->Draw(3, 0);
//}

IMeshRenderer* DirectX11::CreateMeshRenderer( VertexData* data )
{
	return new MeshRenderer( data );
}

void DirectX11::SetClearColor(float r, float g, float b, float a)
{
	clear_color[0] = r;
	clear_color[1] = g;
	clear_color[2] = b;
	clear_color[3] = a;
}

void DirectX11::UpdateCamera(const Camera& camera)
{
	MeshRenderer::UpdateCamera(camera);
}
