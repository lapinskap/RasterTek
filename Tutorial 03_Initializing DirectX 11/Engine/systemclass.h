#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include "inputclass.h"
#include "applicationclass.h"

class SystemClass
{
public:
	
	SystemClass();
	~SystemClass();

	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

	bool Frame();
	void InitializeWindows(uint& screenWidth, uint& screenHeight);
	void ShutdownWindows();

private:

	LPCWSTR _applicationName;
	HINSTANCE _hinstance;
	HWND _hwnd;

	InputClass _input; // This object will be used to handle reading the keyboard input from the user.
	std::unique_ptr<ApplicationClass> _application;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static SystemClass* ApplicationHandle = 0;
