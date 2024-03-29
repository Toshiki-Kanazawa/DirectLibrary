#include "GameApp.h"
#include "ModelObject.h"
#include <vector>

GameLibrary* ModelObject::gameLib = nullptr;

//プレイヤーの設定
#define P_SIZE (0.5f)
#define P_R (0.34f)
#define P_G (0.63f)
#define P_B (1.0f)

//床の設定
#define F_SIZE (10.0f)
#define F_R (0.62f)
#define F_G (1.0f)
#define F_B (0.37f)

//敵キャラの設定
#define E_SIZE (0.5f)
#define E_R (1.0f)
#define E_G (0.0f)
#define E_B (0.0f)


std::vector<Vertex> playerVertex =
{
    Vertex(-P_SIZE,-P_SIZE,-P_SIZE, P_R, P_G, P_B, 1.0f),//0
    Vertex(+P_SIZE,-P_SIZE,-P_SIZE, P_R, P_G, P_B, 1.0f),//1
    Vertex(-P_SIZE,-P_SIZE,+P_SIZE, P_R, P_G, P_B, 1.0f),//2
    Vertex(+P_SIZE,-P_SIZE,+P_SIZE, P_R, P_G, P_B, 1.0f),//3

    Vertex(-P_SIZE,+P_SIZE,-P_SIZE, P_R, P_G, P_B, 1.0f),//4
    Vertex(+P_SIZE,+P_SIZE,-P_SIZE, P_R, P_G, P_B, 1.0f),//5
    Vertex(-P_SIZE,+P_SIZE,+P_SIZE, P_R, P_G, P_B, 1.0f),//6
    Vertex(+P_SIZE,+P_SIZE,+P_SIZE, P_R, P_G, P_B, 1.0f),//7
};

std::vector<WORD> playerIndex =
{
     0,4,1, 4,5,1,
     2,6,0, 6,4,0,
     3,5,7, 5,3,1,
     4,6,7, 7,5,4,
};

std::vector<Vertex> floorVertex =
{
    Vertex(-F_SIZE,-0.5f,-F_SIZE, F_R, F_G, F_B, 1.0f),//0
    Vertex(+F_SIZE,-0.5f,-F_SIZE, F_R, F_G, F_B, 1.0f),//1
    Vertex(-F_SIZE,-0.5f,+F_SIZE, F_R, F_G, F_B, 1.0f),//2
    Vertex(+F_SIZE,-0.5f,+F_SIZE, F_R, F_G, F_B, 1.0f),//3
};

std::vector<WORD> floorIndex =
{
    0,2,1, 2,3,1,
};

//敵データ
std::vector<Vertex> enemyVertex = 
{
    Vertex(-E_SIZE,-E_SIZE,-E_SIZE, E_R, E_G, E_B, 1.0f),//0
    Vertex(+E_SIZE,-E_SIZE,-E_SIZE, E_R, E_G, E_B, 1.0f),//1
    Vertex(-E_SIZE,-E_SIZE,+E_SIZE, E_R, E_G, E_B, 1.0f),//2
    Vertex(+E_SIZE,-E_SIZE,+E_SIZE, E_R, E_G, E_B, 1.0f),//3

    Vertex(-E_SIZE,+E_SIZE,-E_SIZE, E_R, E_G, E_B, 1.0f),//4
    Vertex(+E_SIZE,+E_SIZE,-E_SIZE, E_R, E_G, E_B, 1.0f),//5
    Vertex(-E_SIZE,+E_SIZE,+E_SIZE, E_R, E_G, E_B, 1.0f),//6
    Vertex(+E_SIZE,+E_SIZE,+E_SIZE, E_R, E_G, E_B, 1.0f),//7
};
std::vector<WORD> enemyIndex =
{
     0,4,1, 4,5,1,
     2,6,0, 6,4,0,
     3,5,7, 5,3,1,
     4,6,7, 7,5,4,
};

//モデルのコンストラクタ
ModelObject::ModelObject(const std::wstring& filePath)
{
    //変数の初期化
	posX = 0.0f;
	posY = 0.0f;
	posZ = 0.0f;
	rotX = 0.0f;
	rotY = 0.0f;
	rotZ = 0.0f;
	scaleX = 1.0f;
	scaleY = 1.0f;
	scaleZ = 1.0f;

    //頂点データの作成(仮)
    //TODO::ここをファイルから読み込むようにする
    vertexData = new VertexData();
    if (filePath == L"Player.txt")
    {
        vertexData->vertex = playerVertex.data();
        vertexData->size = playerVertex.size();
        vertexData->indexes = playerIndex.data();
        vertexData->indexSize = playerIndex.size();
    }
    else if (filePath == L"Floor.txt")
    {
        vertexData->vertex = floorVertex.data();
        vertexData->size = floorVertex.size();
        vertexData->indexes = floorIndex.data();
        vertexData->indexSize = floorIndex.size();
    }
    else
    {
        vertexData->vertex = enemyVertex.data();
        vertexData->indexes = enemyIndex.data();
        vertexData->size = enemyVertex.size();
        vertexData->indexSize = enemyIndex.size();
    }

    //メッシュを作成する
    mesh = gameLib->CreateMeshRenderer(vertexData);
}

//モデルのデストラクタ
ModelObject::~ModelObject()
{
    delete mesh;
    delete vertexData;
}

//モデルの描画処理
void ModelObject::Render()
{
    //パラメータを設定する
    auto gameObject = GameObject();
    gameObject.pos.x = posX;
    gameObject.pos.y = posY;
    gameObject.pos.z = posZ;
    gameObject.rot = rotZ;
    gameObject.scale.x = scaleX;
    gameObject.scale.y = scaleY;
    gameObject.scale.z = scaleZ;
    mesh->SetData(gameObject);
    //mesh->SetContextBuffer(gameObject, *camera);

    //描画
    mesh->Draw();
}
