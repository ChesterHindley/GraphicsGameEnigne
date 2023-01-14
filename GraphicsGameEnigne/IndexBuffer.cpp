#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(std::vector<short int>& indices, Graphics& g) : Bindable(g), size{indices.size()}
{
	D3D11_BUFFER_DESC bdc{};
	bdc.ByteWidth = static_cast<UINT>(indices.size() * sizeof(int));
	bdc.Usage = D3D11_USAGE_DEFAULT;
	bdc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bdc.StructureByteStride = static_cast <UINT>(sizeof(int));

	D3D11_SUBRESOURCE_DATA sdat{};
	sdat.pSysMem = indices.data();
	sdat.SysMemPitch = sizeof(int);
	gfx.pDevice->CreateBuffer(&bdc, &sdat, &pIndexBuffer);
}

auto IndexBuffer::getSize() const
{
	return size;
}

void IndexBuffer::bind()
{
	gfx.pDeviceContext->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
}
