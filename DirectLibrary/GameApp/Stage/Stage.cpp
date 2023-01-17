#include "Stage.h"

Stage::Stage() {
	Floor = new ModelObject( L"Floor.txt" );
}

Stage::~Stage() {
	delete Floor;
}

void Stage::Start() {

}

void Stage::Update() {

}

void Stage::Render() {
	Floor->Render();
}