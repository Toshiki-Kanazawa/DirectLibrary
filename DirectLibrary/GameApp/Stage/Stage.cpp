#include "Stage.h"

Stage::Stage() {
	Floor = new ModelObject( L"Floor.txt" );

	WorldSize_min = Vector3(-100, -100, -100);
	WorldSize_max = Vector3(100, 100, 100);
}

Stage::~Stage() {
	delete Floor;
}

Vector3 Stage::GetPlayerNextPos(Vector3 pl_pos, Vector3 pl_size)
{
	Vector3 resultPos = pl_pos;

	if (pl_pos.x - pl_size.x < WorldSize_min.x) {
		resultPos.x = WorldSize_min.x + pl_size.x;
	}
	if (pl_pos.x - pl_size.x > WorldSize_max.x) {
		resultPos.x = WorldSize_max.x - pl_size.x;
	}
	if (pl_pos.y - pl_size.y < WorldSize_min.y) {
		resultPos.y = WorldSize_min.y + pl_size.y;
	}
	if (pl_pos.y - pl_size.y > WorldSize_max.y) {
		resultPos.y = WorldSize_max.y - pl_size.y;
	}
	if (pl_pos.z - pl_size.z < WorldSize_min.z) {
		resultPos.z = WorldSize_min.z + pl_size.z;
	}
	if (pl_pos.z - pl_size.z > WorldSize_max.z) {
		resultPos.z = WorldSize_max.z - pl_size.z;
	}

	return resultPos;
}

void Stage::Start() {
	Floor->posX = 0.0f;
	Floor->posY = 0.0f;
	Floor->posZ = 0.0f;
}

void Stage::Update() {

}

void Stage::Render() {
	Floor->Render();
}