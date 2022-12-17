#include <stdio.h>
#include "DirectX.h"
#include <Windows.h>

#pragma comment(lib,"d3d11.lib")

ID3D11Device* DirectX::device = nullptr;			//�f�o�C�X
ID3D11DeviceContext* DirectX::context = nullptr;	//�R���e�L�X�g
IDXGISwapChain* DirectX::swapChain = nullptr;		//�X���b�v�`�F�C��
ID3D11RenderTargetView* DirectX::renderTargetView = nullptr;	//�����_�[�^�[�Q�b�g�r���[
ID3D11Texture2D* DirectX::texture = nullptr;					//�����_�[�e�N�X�`���[
ID3D11DepthStencilView* DirectX::depthStencilView = nullptr;	//�f�v�X�X�e���V���r���[
char* DirectX::vsData = nullptr;
char* DirectX::psData = nullptr;
ID3D11VertexShader* DirectX::vsShader = nullptr;
ID3D11PixelShader* DirectX::psShader = nullptr;
ID3D11InputLayout* DirectX::inputLayout = nullptr;
ID3D11Buffer* DirectX::vertexBuffer = nullptr;

Vertex vertexList[]
{
   { { -0.2f,  0.2f, 0.2f }, { 1.0f, 1.0f, 1.0f, 1.0f } },
	{ {  0.2f, -0.2f, 0.2f }, { 1.0f, 1.0f, 1.0f, 1.0f } },
	{ { -0.2f, -0.2f, 0.2f }, { 1.0f, 1.0f, 1.0f, 1.0f } },
};

D3D11_INPUT_ELEMENT_DESC inputLayoutData[]{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,	 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

//�X���b�v�`�F�C���𐶐�����Ƃ��ɕK�v�ȃp�����[�^��p�ӂ���
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

//�f�o�C�X�ƃX���b�v�`�F�C���ƃR���e�L�X�g���쐬����
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

//�����_�[�^�[�Q�b�g�r���[�̍쐬
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

//�f�v�X�X�e���V���r���[�̍쐬
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

bool DirectX::CreateShader()
{
	FILE* fp = nullptr;
	fopen_s(&fp, "Shader/vsShader.cso", "rb");
	if (fp == nullptr)
	{
		return false;	//�V�F�[�_�ǂݍ��߂Ȃ�����
	}

	//�t�@�C���̒������擾����
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);

	//�t�@�C���̓ǂݍ��݈ʒu��擪�ɖ߂�
	fseek(fp, 0, SEEK_SET);

	//�o�C�g�z����t�@�C���̒����ō쐬����
	vsData = new char[size];

	//�z��ɓǂݍ��񂾃f�[�^������
	fread_s(vsData, size, size, 1, fp);

	//�ǂݍ��񂾃t�@�C�����N���[�Y����
	fclose(fp);

	fp = nullptr;
	fopen_s(&fp, "Shader/psShader.cso", "rb");

	if (fp == nullptr)
	{
		return false;	//�V�F�[�_�ǂݍ��߂Ȃ�����
	}

	//�t�@�C���̒������擾����
	fseek(fp, 0, SEEK_END);
	int size2 = ftell(fp);

	//�t�@�C���̓ǂݍ��݈ʒu��擪�ɖ߂�
	fseek(fp, 0, SEEK_SET);

	//�o�C�g�z����t�@�C���̒����ō쐬����
	psData = new char[size2];

	//�z��ɓǂݍ��񂾃f�[�^������
	fread_s(psData, size2, size2, 1, fp);

	//�ǂݍ��񂾃t�@�C�����N���[�Y����
	fclose(fp);

	//���_�V�F�[�_���쐬����
	if (FAILED(device->CreateVertexShader(vsData, size, nullptr, &vsShader)))
	{
		return false;
	}

	//�s�N�Z���V�F�[�_���쐬����
	if (FAILED(device->CreatePixelShader(psData, size2, nullptr, &psShader)))
	{
		return false;
	}

	//���_�o�b�t�@�̍쐬�ɕK�v�ȍ\���̂��쐬����
	D3D11_BUFFER_DESC buffer_desc;
	buffer_desc.ByteWidth = sizeof(Vertex) * 3;
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;
	buffer_desc.StructureByteStride = sizeof(Vertex);

	//���_�o�b�t�@�̍쐬�ɕK�v�ȍ\���̂��쐬���邻�̂Q
	D3D11_SUBRESOURCE_DATA init_data;
	init_data.pSysMem = vertexList;
	init_data.SysMemPitch = 0;
	init_data.SysMemSlicePitch = 0;

	//���_�o�b�t�@���쐬����
	if (FAILED(device->CreateBuffer(&buffer_desc, &init_data, &vertexBuffer)))
	{
		return false;
	}

	//���̓��C�A�E�g���쐬����
	if (FAILED(device->CreateInputLayout(inputLayoutData,
		ARRAYSIZE(inputLayoutData),
		vsData,
		size,
		&inputLayout)))
	{
		return false;
	}


	return true;
}

//DirectX�̏���������
bool DirectX::Init()
{
	HWND window_handle = FindWindow(L"DirectLibrary", nullptr);

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
	D3D11_VIEWPORT view_port;
	view_port.TopLeftX = 0;							// ����X���W
	view_port.TopLeftY = 0;							// ����Y���W
	view_port.Width = (rect.right - rect.left);		// ����
	view_port.Height = (rect.bottom - rect.top);	// �c��
	view_port.MinDepth = 0.0f;						// �ŏ��[�x
	view_port.MaxDepth = 1.0f;						// �ő�[�x

	context->RSSetViewports(
		1,					// �ݒ肷��r���[�|�[�g�̐�
		&view_port);		// �ݒ肷��r���[�|�[�g���̃|�C���^
	//�V�F�[�_�[�̍쐬
	if (!CreateShader())
	{
		return false;
	}

	return true;
}

//DirectX�̉���֐�
void DirectX::Release()
{
	if (vsShader != nullptr) vsShader->Release();
	if (psShader != nullptr) psShader->Release();

	if (vsData != nullptr) delete vsData;
	if (psData != nullptr) delete psData;

	if (depthStencilView != nullptr) depthStencilView->Release();
	if (texture != nullptr) texture->Release();
	if (renderTargetView != nullptr) renderTargetView->Release();
	if (swapChain != nullptr) swapChain->Release();
	if (context != nullptr) context->Release();
	if (device != nullptr) device->Release();
}

//�`��J�n�֐�
void DirectX::StartRendering()
{
	float clear_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

	InputManager::Update();

	if (InputManager::Trg(KeyType::A))
	{
		vertexList[0].pos[1] = 1.0f;

		clear_color[0] = 1.0f;
	}
	if (InputManager::Rel(KeyType::Space))
	{
		clear_color[1] = 1.0f;
	}
	if (InputManager::On(KeyType::_2))
	{
		vertexList[0].pos[1] = 1.0f;
		clear_color[2] = 1.0f;
	}

	context->ClearRenderTargetView(renderTargetView, clear_color);
	context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

//�`��I���֐�
void DirectX::FinishRendering()
{
	swapChain->Present(0, 0);
}

//�|���S����`�悷��֐�
void DirectX::RenderingPolygon()
{
	UINT strides = sizeof(Vertex);
	UINT offset = 0;

	context->UpdateSubresource(vertexBuffer, 0, NULL, &vertexList, 0, 0);
	context->IASetVertexBuffers(0, 1, &vertexBuffer, &strides, &offset );
	context->IASetInputLayout(inputLayout);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->VSSetShader(vsShader, NULL, 0);
	context->PSSetShader(psShader, NULL, 0);
	context->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	context->Draw(3, 0);
}