#include "Stage.h"

Stage::Stage() {
	Floor = new ModelObject( L"Floor.txt" );
}

Stage::~Stage() {
	delete Floor;
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