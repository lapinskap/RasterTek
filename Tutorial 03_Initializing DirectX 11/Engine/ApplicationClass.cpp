#include "ApplicationClass.h"


ApplicationClass::ApplicationClass(uint screenWidth, uint screenHeight, HWND hwnd)
	: _direct3D(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR)
{
	// TODO: Handle the error if the Direct3D object is not created.
}

bool ApplicationClass::Render()
{
	// Clear the buffers to begin the scene.
	_direct3D.BeginScene(0.5f, 0.5f, 0.5f, 1.0f);


	// Present the rendered scene to the screen.
	_direct3D.EndScene();

	return true;
	// ???????
}

bool ApplicationClass::Frame()
{
	return Render();
}

