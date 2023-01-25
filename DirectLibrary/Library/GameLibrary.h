#pragma once
#include <Windows.h>
#include "Vector3.h"
#include "IMeshRenderer.h"

class GameLibrary
{
public:
	virtual bool Init(HWND window_handle) = 0;
	virtual void Release() = 0;
	virtual void StartRendering() = 0;
	virtual void FinishRendering() = 0;

	virtual IMeshRenderer* CreateMeshRenderer( VertexData* data ) = 0;
	virtual void SetClearColor(float r, float g, float b, float a) = 0;

};