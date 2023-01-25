#pragma once

class Camera
{
public:
	static float posX;
	static float posY;
	static float posZ;

	static float focusX;
	static float focusY;
	static float focusZ;
};


class Vertex
{
public:
	Vertex(float x = 0.0f, float y = 0.0f, float z = 0.0f, float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f): x(x), y(y), z(z), r(r), g(g), b(b), a(a)
	{

	}

	float x, y, z;
	float r, g, b, a;
	//float u, v;
};

class VertexData
{
public:
	Vertex* vertex;	//頂点配列
	WORD* indexes;	//インデックス配列
	int size;		//頂点配列の長さ
	int indexSize;	//インデックス配列の長さ
};

//GameAppからアクセスするためのインターフェイスクラス
class IMeshRenderer
{
public:
	virtual void SetData(const GameObject& gameObject) = 0;
	//virtual bool SetData( VertexData* data) = 0;
	//virtual bool SetData(Vertex* vertex, int size) = 0;
	virtual void Draw() = 0;
	//virtual void SetContextBuffer(const GameObject& gameObject, const Camera& camera ) = 0;
};
