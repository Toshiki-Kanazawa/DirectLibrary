#include "ModelObject.h"

ModelObject::ModelObject(const std::wstring& filePath)
{
	posX = 0.0f;
	posY = 0.0f;
	posZ = 0.0f;
	rotX = 0.0f;
	rotY = 0.0f;
	rotZ = 0.0f;
	scaleX = 1.0f;
	scaleY = 1.0f;
	scaleZ = 1.0f;
}

ModelObject::~ModelObject()
{
	//TODO::
}

void ModelObject::Render()
{
	//TODO::
}
