#pragma once

#include "../ModelObject.h"

class Stage{
private:
	ModelObject* Floor;
public:
	Stage();
	~Stage();

	void Start();
	void Update();
	void Render();
};