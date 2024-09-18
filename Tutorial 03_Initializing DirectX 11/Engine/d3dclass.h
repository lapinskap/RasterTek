#pragma once

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>
#include <directxmath.h>
#include <memory>
#include <string>
#include <vector>

using uint = unsigned int;

template <typename T>
struct ReleasingPtr
{
	ReleasingPtr() = default;
	ReleasingPtr(const ReleasingPtr&) = delete;
	ReleasingPtr& operator=(const ReleasingPtr&) = delete;
	ReleasingPtr(ReleasingPtr&& other) noexcept
	{
		_ptr = other._ptr;
		other._ptr = nullptr;
	}
	ReleasingPtr& operator=(ReleasingPtr&& other) noexcept
	{
		if (this != &other)
		{
			if (_ptr)
				_ptr->Release();
                
			_ptr = other._ptr;
			other._ptr = nullptr;
		}
		return *this;
	}

    ~ReleasingPtr()
    {
        if (_ptr)
            _ptr->Release();
	}

	T* operator->()
	{
		return _ptr;
	}

	T* get()
	{
		return _ptr;
	}

	T** operator&()
	{
		return &_ptr;
	}

	explicit operator bool() const
	{
		return _ptr != nullptr;
	}

private:

	T* _ptr = nullptr;
};

class D3DClass
{
public:

	D3DClass(uint screenWidth, uint screenHeight, bool vsync, HWND hwnd, bool fullscreen, float screenDepth, float screenNear);
    ~D3DClass();

    void BeginScene(float red, float green, float blue, float alpha);
    void EndScene();

    ID3D11Device* GetDevice();
    ID3D11DeviceContext* GetDeviceContext();

    void GetProjectionMatrix(DirectX::XMMATRIX&);
    void GetWorldMatrix(DirectX::XMMATRIX&);
    void GetOrthoMatrix(DirectX::XMMATRIX&);

    const std::string& GetVideoCardInfo() const;

    void SetBackBufferRenderTarget();
    void ResetViewport();

private:

	bool Init2(HWND hwnd, uint numerator, uint denominator, bool fullscreen, uint screenWidth, uint screenHeight, float screenDepth, float screenNear);

    bool _vsyncEnabled = false;
    int _videoCardMemory = 0;
    std::string _videoCardDescription;
    ReleasingPtr<IDXGISwapChain> _swapChain;
    ReleasingPtr<ID3D11Device> _device;
    ReleasingPtr<ID3D11DeviceContext> _deviceContext;
    ReleasingPtr<ID3D11RenderTargetView> _renderTargetView;
    ReleasingPtr<ID3D11Texture2D> _depthStencilBuffer;
    ReleasingPtr<ID3D11DepthStencilState> _depthStencilState;
    ReleasingPtr<ID3D11DepthStencilView> _depthStencilView;
    ReleasingPtr<ID3D11RasterizerState> _rasterState;
    DirectX::XMMATRIX _projectionMatrix;
    DirectX::XMMATRIX _worldMatrix;
    DirectX::XMMATRIX _orthoMatrix;
    D3D11_VIEWPORT _viewport;
};

