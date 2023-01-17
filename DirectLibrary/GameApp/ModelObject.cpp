#include "GameApp.h"
#include "ModelObject.h"

Camera* ModelObject::camera = nullptr;
GameLibrary* ModelObject::gameLib = nullptr;

//���f�[�^
Vertex vertexList[]
{
    Vertex(-0.5f,  0.5f, -0.5f , 1.0f, 0.0f, 0.0f, 1.0f),
    Vertex(0.5f,  0.5f, -0.5f , 1.0f, 0.0f, 0.0f, 1.0f),
    Vertex(-0.5f, -0.5f, -0.5f , 1.0f, 0.0f, 0.0f, 1.0f),
    Vertex(0.5f, -0.5f, -0.5f , 1.0f, 0.0f, 0.0f, 1.0f),
    Vertex(-0.5f,  0.5f,  0.5f , 0.0f, 1.0f, 1.0f, 1.0f),
    Vertex(-0.5f, -0.5f,  0.5f , 0.0f, 1.0f, 1.0f, 1.0f),
    Vertex(0.5f,  0.5f,  0.5f , 0.0f, 1.0f, 1.0f, 1.0f),
    Vertex(0.5f, -0.5f,  0.5f , 0.0f, 1.0f, 1.0f, 1.0f),
    Vertex(-0.5f,  0.5f,  0.5f , 1.0f, 1.0f, 0.0f, 1.0f),
    Vertex(-0.5f,  0.5f, -0.5f , 1.0f, 1.0f, 0.0f, 1.0f),
    Vertex(-0.5f, -0.5f,  0.5f , 1.0f, 1.0f, 0.0f, 1.0f),
    Vertex(-0.5f, -0.5f, -0.5f , 1.0f, 1.0f, 0.0f, 1.0f),
    Vertex(0.5f,  0.5f,  0.5f , 0.0f, 0.0f, 1.0f, 1.0f),
    Vertex(0.5f, -0.5f,  0.5f , 0.0f, 0.0f, 1.0f, 1.0f),
    Vertex(0.5f,  0.5f, -0.5f , 0.0f, 0.0f, 1.0f, 1.0f),
    Vertex(0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f),
    Vertex(-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f),
    Vertex(0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f),
    Vertex(-0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f),
    Vertex(0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f),
    Vertex(-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f),
    Vertex(-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f),
    Vertex(0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f),
    Vertex(0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f),
};
WORD indexList[]
{
     0,  1,  2,     3,  2,  1,
     4,  5,  6,     7,  6,  5,
     8,  9, 10,    11, 10,  9,
    12, 13, 14,    15, 14, 13,
    16, 17, 18,    19, 18, 17,
    20, 21, 22,    23, 22, 21,
};

//���f���̃R���X�g���N�^
ModelObject::ModelObject(const std::wstring& filePath)
{
    //�ϐ��̏�����
	posX = 0.0f;
	posY = 0.0f;
	posZ = 0.0f;
	rotX = 0.0f;
	rotY = 0.0f;
	rotZ = 0.0f;
	scaleX = 1.0f;
	scaleY = 1.0f;
	scaleZ = 1.0f;

    //���_�f�[�^�̍쐬(��)
    //TODO::�������t�@�C������ǂݍ��ނ悤�ɂ���
    vertexData = new VertexData();
    vertexData->vertex = vertexList;
    vertexData->indexes = indexList;
    vertexData->size = 24;
    vertexData->indexSize = 36;

    //���b�V�����쐬����
    mesh = gameLib->CreateMeshRenderer(vertexData);
}

//���f���̃f�X�g���N�^
ModelObject::~ModelObject()
{
    delete mesh;
    delete vertexData;
}

//���f���̕`�揈��
void ModelObject::Render()
{
    //�p�����[�^��ݒ肷��
    auto gameObject = GameObject();
    gameObject.pos.x = posX;
    gameObject.pos.y = posY;
    gameObject.pos.z = posZ;
    gameObject.rot = rotZ;
    gameObject.scale.x = scaleX;
    gameObject.scale.y = scaleY;
    gameObject.scale.z = scaleZ;
    mesh->SetContextBuffer(gameObject, *camera);

    //�`��
    mesh->Draw();
}
