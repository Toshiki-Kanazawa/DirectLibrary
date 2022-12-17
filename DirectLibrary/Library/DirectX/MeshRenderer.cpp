#include "DirectX.h"

char* MeshRenderer::vsData = nullptr;
char* MeshRenderer::psData = nullptr;
ID3D11VertexShader* MeshRenderer::vsShader = nullptr;
ID3D11PixelShader* MeshRenderer::psShader = nullptr;
ID3D11InputLayout* MeshRenderer::inputLayout = nullptr;

D3D11_INPUT_ELEMENT_DESC inputLayoutData[]{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,	 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};


bool MeshRenderer::Init()
{
	auto device = DirectX::device;

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

void MeshRenderer::Release()
{
	if (vsShader != nullptr) vsShader->Release();
	if (psShader != nullptr) psShader->Release();

	if (vsData != nullptr) delete vsData;
	if (psData != nullptr) delete psData;
}

MeshRenderer::MeshRenderer(Vertex* vertex, int size)
{
	this->vertex = vertex;
	this->size = size;

	//���_�o�b�t�@�̍쐬�ɕK�v�ȍ\���̂��쐬����
	D3D11_BUFFER_DESC buffer_desc;
	buffer_desc.ByteWidth = sizeof(Vertex) * size;
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;
	buffer_desc.StructureByteStride = sizeof(Vertex);

	//���_�o�b�t�@�̍쐬�ɕK�v�ȍ\���̂��쐬���邻�̂Q
	D3D11_SUBRESOURCE_DATA init_data;
	init_data.pSysMem = vertex;
	init_data.SysMemPitch = 0;
	init_data.SysMemSlicePitch = 0;

	//���_�o�b�t�@���쐬����
	if (FAILED(DirectX::device->CreateBuffer(&buffer_desc, &init_data, &vertexBuffer)))
	{
		return;
	}

}

MeshRenderer::~MeshRenderer()
{
	vertex = nullptr;
	if (vertexBuffer != nullptr) vertexBuffer->Release();
}

bool MeshRenderer::SetData( VertexData* data)
{
	//���_�o�b�t�@�̍쐬�ɕK�v�ȍ\���̂��쐬����
	D3D11_BUFFER_DESC buffer_desc;
	buffer_desc.ByteWidth = sizeof(Vertex) * data->size;
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;
	buffer_desc.StructureByteStride = sizeof(Vertex);

	//���_�o�b�t�@�̍쐬�ɕK�v�ȍ\���̂��쐬���邻�̂Q
	D3D11_SUBRESOURCE_DATA init_data;
	init_data.pSysMem = data->vertex;
	init_data.SysMemPitch = 0;
	init_data.SysMemSlicePitch = 0;

	//���_�o�b�t�@���쐬����
	if (FAILED(DirectX::device->CreateBuffer(&buffer_desc, &init_data, &vertexBuffer)))
	{
		return false;
	}


	//���_�o�b�t�@���X�V����
	vertex = data->vertex;
	size = data->size;

	return true;
}

bool MeshRenderer::SetData(Vertex* vertex, int size)
{
	//���_�o�b�t�@���X�V����
	this->vertex = vertex;
	this->size = size;

	return true;
}

void MeshRenderer::Draw()
{
	UINT strides = sizeof(Vertex);
	UINT offset = 0;
	
	//���_�f�[�^���X�V����
	DirectX::context->UpdateSubresource(vertexBuffer, 0, NULL, vertex, 0, 0);

	//���_�f�[�^����������
	DirectX::context->IASetVertexBuffers(0, 1, &vertexBuffer, &strides, &offset);

	//���̓��C�A�E�g��ݒ肷��
	DirectX::context->IASetInputLayout(inputLayout);

	//�v���~�e�B�u��ݒ肷��
	DirectX::context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//���_�V�F�[�_�[��ݒ肷��
	DirectX::context->VSSetShader(vsShader, NULL, 0);

	//�s�N�Z���V�F�[�_�[��ݒ肷��
	DirectX::context->PSSetShader(psShader, NULL, 0);

	//�`�悷��
	DirectX::context->Draw(size, 0);
}
