#pragma once
#include <string>

class ModelObject
{
public:
	ModelObject(const std::wstring& filePath);
	~ModelObject();

	//À•W•Ï”
	float posX;
	float posY;
	float posZ;

	//‰ñ“]•Ï”
	float rotX;
	float rotY;
	float rotZ;

	//Šg‘å—¦•Ï”
	float scaleX;
	float scaleY;
	float scaleZ;

	//ƒ‚ƒfƒ‹‚ğ•`‰æ‚·‚éŠÖ”
	void Render();
};