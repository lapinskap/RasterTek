#include "SystemClass.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	// Create the system object.
	SystemClass System;

	// Run the system object.
	System.Run();

	return 0;
}