#pragma once

class Vector3
{
public:
	float x, y, z;
	Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}
};

class GameObject
{
public:
	Vector3 pos;
	Vector3 rot;
	Vector3 scale;
	GameObject()
	{
		pos = Vector3(0, 0, 0);
		rot = Vector3(0, 0, 0);
		scale = Vector3(1, 1, 1);
	}
};