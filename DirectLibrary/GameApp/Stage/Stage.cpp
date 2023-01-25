#include "Stage.h"

Stage* Stage::instance = nullptr;

Stage::Stage() {

	instance = this;

	Floor = new ModelObject( L"Floor.txt" );

	WorldSize_min = Vector3(-10, -10, -10);
	WorldSize_max = Vector3(10, 10, 10);
}

Stage::~Stage() {
	if (instance == this)
	{
		instance = nullptr;
	}
	delete Floor;
}

Vector3 Stage::GetPlayerNextPos(Vector3 pl_pos, Vector3 pl_size)
{
	Vector3 resultPos = pl_pos;

	if (pl_pos.x - pl_size.x < WorldSize_min.x) {
		resultPos.x = WorldSize_min.x + pl_size.x;
	}
	if (pl_pos.x - pl_size.x > WorldSize_max.x) {
		resultPos.x = WorldSize_max.x + pl_size.x;
	}
	if (pl_pos.y - pl_size.y < WorldSize_min.y) {
		resultPos.y = WorldSize_min.y + pl_size.y;
	}
	if (pl_pos.y - pl_size.y > WorldSize_max.y) {
		resultPos.y = WorldSize_max.y + pl_size.y;
	}
	if (pl_pos.z - pl_size.z < WorldSize_min.z) {
		resultPos.z = WorldSize_min.z + pl_size.z;
	}
	if (pl_pos.z - pl_size.z > WorldSize_max.z) {
		resultPos.z = WorldSize_max.z + pl_size.z;
	}

	return resultPos;
}

void Stage::Start() {
	Floor->posX = 10.0f;
	Floor->posY = 0.0f;
	Floor->posZ = 10.0f;
}

void Stage::Update() {

}

void Stage::Render() {
	Floor->Render();
}

bool Stage::GetOutStageFlag(Vector3 nowPos)
{
	bool outStage = false;

	if (nowPos.x < instance->WorldSize_min.x) outStage = true;
	if (nowPos.x > instance->WorldSize_max.x) outStage = true;
	if (nowPos.y < instance->WorldSize_min.y) outStage = true;
	if (nowPos.y > instance->WorldSize_max.y) outStage = true;
	if (nowPos.z < instance->WorldSize_min.z) outStage = true;
	if (nowPos.z > instance->WorldSize_max.z) outStage = true;

	return outStage;
}
