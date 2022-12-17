#pragma once

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
	Vertex* vertex;
	int size;
};

//GameAppからアクセスるするためのインターフェイスクラス
class IMeshRenderer
{
public:
	virtual bool SetData( VertexData* data) = 0;
	virtual bool SetData(Vertex* vertex, int size) = 0;
	virtual void Draw() = 0;
};
