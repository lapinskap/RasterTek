#pragma once

#include "Common.h"
#include "D3D.h"

const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.3f;

class Application
{
public:
	
	Application(uint screenWidth, uint screenHeight, HWND hwnd);

	bool Frame();

private:

	bool Render();

	D3D _direct3D;
};
