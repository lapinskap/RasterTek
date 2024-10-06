#pragma once

#include <d3d11.h>
#include <directxmath.h>
#include "ReleasePtr.h"

class Model
{
public:
	Model(ID3D11Device* device);

	void Render(ID3D11DeviceContext* deviceContext);

	int GetIndexCount();

private:
	struct VertexType
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT4 color;
	};

	void InitializeBuffers(ID3D11Device* device);
	void RenderBuffers(ID3D11DeviceContext* deviceContext);

	ReleasePtr<ID3D11Buffer> _vertexBuffer;
	ReleasePtr<ID3D11Buffer> _indexBuffer;
	int _vertexCount = 0;
	int _indexCount = 0;
};