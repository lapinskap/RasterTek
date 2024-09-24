#include "Application.h"


Application::Application(uint screenWidth, uint screenHeight, HWND hwnd)
	: _direct3D(D3D::InitParams{ hwnd, screenWidth, screenHeight, SCREEN_NEAR, SCREEN_DEPTH, VSYNC_ENABLED, FULL_SCREEN })
{
	// Create the camera object.
	_camera = new Camera;

	// Set the initial position of the camera.
	_camera->SetPosition(0.0f, 0.0f, -5.0f);

	// Create and initialize the model object.
	_model = new Model;

	bool result = _model->Initialize(_direct3D.GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return;
	}

	// Create and initialize the color shader object.
	_colorShader = new ColorShader;

	result = _colorShader->Initialize(_direct3D.GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return;
	}
}

Application::~Application()
{
	// Release the color shader object.
	if (_colorShader)
	{
		_colorShader->Shutdown();
		delete _colorShader;
		_colorShader = nullptr;
	}

	// Release the model object.
	if (_model)
	{
		_model->Shutdown();
		delete _model;
		_model = nullptr;
	}

	// Release the camera object.
	if (_camera)
	{
		delete _camera;
		_camera = nullptr;
	}
}

bool Application::Render()
{
	DirectX::XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;


	// Clear the buffers to begin the scene.
	_direct3D.BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	_camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	_direct3D.GetWorldMatrix(worldMatrix);
	_camera->GetViewMatrix(viewMatrix);
	_direct3D.GetProjectionMatrix(projectionMatrix);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	_model->Render(_direct3D.GetDeviceContext());

	// Render the model using the color shader.
	result = _colorShader->Render(_direct3D.GetDeviceContext(), _model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	_direct3D.EndScene();

	return true;
}

bool Application::Frame()
{
	return Render();
}

