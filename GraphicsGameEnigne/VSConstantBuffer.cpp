#include "VSConstantBuffer.h"
VSConstantBuffer::VSConstantBuffer(Graphics& g) : Bindable(g)
{
    DirectX::XMStoreFloat4x4(&data.matrix, DirectX::XMMatrixTranspose(DirectX::XMMatrixRotationRollPitchYaw(0, 0, 0) *
        DirectX::XMMatrixScaling(1, 1, 1)));

    D3D11_BUFFER_DESC bdc = {};
    bdc.ByteWidth = sizeof(data);
    bdc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
    bdc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
    bdc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    D3D11_SUBRESOURCE_DATA sdat{ .pSysMem = reinterpret_cast<void*>(&data) };


    gfx.pDevice->CreateBuffer(&bdc, &sdat, &constantBuffer);
}

void VSConstantBuffer::bind()
{
    gfx.pDeviceContext->VSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
}

void VSConstantBuffer::update(const DirectX::XMFLOAT4X4& m) // needs to be called before bind, input matrix is already transposed
{
    D3D11_MAPPED_SUBRESOURCE res;
    gfx.pDeviceContext->Map(constantBuffer.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &res);
    *reinterpret_cast<DirectX::XMFLOAT4X4*> (res.pData) = m;
    gfx.pDeviceContext->Unmap(constantBuffer.Get(), 0);
}