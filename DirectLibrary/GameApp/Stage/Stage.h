#pragma once

#include "../ModelObject.h"

class Stage{
public:
	Stage();
	~Stage();

	void Start();
	void Update();
	void Render();
private:
	ModelObject* Floor;
};