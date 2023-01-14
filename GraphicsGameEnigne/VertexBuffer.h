#pragma once
#include <vector>
#include <utility>
#include "Bindable.h"

template <class T>
class VertexBuffer : public Bindable
{
	friend class InputLayout;
	std::vector<T> vertices;
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> InputLayout;


public:
	VertexBuffer(const std::vector<T>& v, Graphics& g) : Bindable(g), vertices{ v }
	{
		D3D11_BUFFER_DESC bdc{};
		bdc.ByteWidth = (UINT)vertices.size() * sizeof(T);//  Size of the buffer in bytes.
		bdc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		bdc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		bdc.StructureByteStride = sizeof(T);

		D3D11_SUBRESOURCE_DATA sdat{ .pSysMem = vertices.data() };
		gfx.pDevice->CreateBuffer(&bdc, &sdat, &vertexBuffer);

	}
	VertexBuffer(std::vector<T>&& v,Graphics& g) :Bindable(g), vertices{ std::move(v) }
		// NEED TO KNOW: SIZE IN BYTES OF THE WHOLE DATA (VOID*), SIZE OF ONE ELEMENT (FOR EXAMPLE NUMBER OF ELEMENTS)
	{
		D3D11_BUFFER_DESC bdc{};
		bdc.ByteWidth = (UINT)vertices.size() * sizeof(T);//  Size of the buffer in bytes.
		bdc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		bdc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		bdc.StructureByteStride = sizeof(T);

		D3D11_SUBRESOURCE_DATA sdat{ .pSysMem = vertices.data() };
		gfx.pDevice->CreateBuffer(&bdc, &sdat, &vertexBuffer);

	}
		void bind() override
		{
			constexpr UINT stride = sizeof(T);
			constexpr UINT offset = 0;
			gfx.pDeviceContext->IASetVertexBuffers(0, 1,vertexBuffer.GetAddressOf(), &stride, &offset);
		}
	
	
};

