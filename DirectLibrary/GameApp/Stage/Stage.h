#pragma once

#include "../ModelObject.h"

class Stage{
private:
	static Stage* instance;

	ModelObject* Floor;

	Vector3 WorldSize_min;
	Vector3 WorldSize_max;
public:
	Stage();
	~Stage();

	Vector3 GetPlayerNextPos(Vector3 pl_pos, Vector3 pl_size);

	void Start();
	void Update();
	void Render();

	static bool GetOutStageFlag(Vector3 nowPos);
};