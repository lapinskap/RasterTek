#pragma once

#include "d3dclass.h"

const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.3f;

class ApplicationClass
{
public:
	
	ApplicationClass(uint screenWidth, uint screenHeight, HWND hwnd);

	bool Frame();

private:

	bool Render();

	D3DClass _direct3D;
};
