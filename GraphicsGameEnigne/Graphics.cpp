#include <vector>
#include "Graphics.h"
#include "Window.h"
#pragma comment(lib,"D3D11.lib")
#include "Shader.h"
#include <filesystem>
#include "VertexBuffer.h"
#include "Drawable.h"
#include "InputLayout.h"
#include "IndexBuffer.h"
Graphics::Graphics(const Window& w)
{
	DXGI_SWAP_CHAIN_DESC scd = {};

	scd.BufferDesc = { 0,0, {0,0}, DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,DXGI_MODE_SCALING_UNSPECIFIED};
	scd.SampleDesc = { 1,0 };
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.Windowed = TRUE;
	scd.BufferCount = 1;
	scd.OutputWindow = w.gethWin();
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	wrl::ComPtr<ID3D11Resource> backBuffer;

	D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
		D3D11_CREATE_DEVICE_DEBUG, nullptr, 0, D3D11_SDK_VERSION, &scd,
		&pSwapChain, &pDevice, nullptr, &pDeviceContext);

	pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &backBuffer);
	pDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, &pRenderTargetView);


	D3D11_DEPTH_STENCIL_DESC depthStencilDesc{ .DepthEnable = true,.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL,.DepthFunc = D3D11_COMPARISON_LESS };
	wrl::ComPtr<ID3D11DepthStencilState> depthStencilState;
	pDevice->CreateDepthStencilState(&depthStencilDesc, &depthStencilState);
	pDeviceContext->OMSetDepthStencilState(depthStencilState.Get(), 1);


	D3D11_TEXTURE2D_DESC dsd{ .Width = (UINT)w.getxSize()-16, .Height = (UINT)w.getySize()-55, .MipLevels = 1, .ArraySize = 1, .Format = DXGI_FORMAT_D16_UNORM, .SampleDesc{1,0},.Usage = D3D11_USAGE_DEFAULT, .BindFlags= D3D11_BIND_DEPTH_STENCIL };

	wrl::ComPtr<ID3D11Texture2D> pDepthTexture;
	auto res = pDevice->CreateTexture2D(&dsd, nullptr, &pDepthTexture);

	D3D11_DEPTH_STENCIL_VIEW_DESC dsdesc{ .Format = DXGI_FORMAT_D16_UNORM , .ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D};
	
	res = pDevice->CreateDepthStencilView(pDepthTexture.Get(),&dsdesc, &pDepthStencilView);


	pDeviceContext->OMSetRenderTargets(1, pRenderTargetView.GetAddressOf(), pDepthStencilView.Get());




	D3D11_VIEWPORT vp{ 0 };
	vp.Width = static_cast<FLOAT>(w.getxSize());
	vp.Height = static_cast<FLOAT>(w.getySize());
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	pDeviceContext->RSSetViewports(1u, &vp);
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);



}

HRESULT Graphics::endFrame()
{
	constexpr FLOAT color[4] = { 0,0,0,1 };
	auto res = pSwapChain->Present(1, 0);
	pDeviceContext->ClearDepthStencilView(pDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1, 0);
	pDeviceContext->ClearRenderTargetView(pRenderTargetView.Get(), color);
	return res;
}

void Graphics::drawTriangle()
{
	Drawable triangle(*this);
	struct Vertex { float x; float y; float z; float r; float g; float b; };
	std::vector<Vertex> vertices{
	   {-0.5,-0.5,0.5,1,0,0},
		{0,0.5,0,0,1,0},
		{0.5,-0.5,0.5,0,0,1},
		{0,-0.5,-0.5,1,0,1},
	};

	triangle.addBind(std::make_unique<VertexBuffer<Vertex>>(std::move(vertices), *this));

	std::vector<short int> indices =
	{
		0,1,2,
		0,3,1,
		2,1,3,
		2,3,0,
	};
	triangle.addBind(std::make_unique<IndexBuffer>(indices, *this));

	const std::vector<D3D11_INPUT_ELEMENT_DESC> idc =  // tell vshader what is in vertex buffer ?? ???  ? ?
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"COLOR",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	auto sh = std::make_unique<Shader<ID3D11VertexShader>>("..\\x64\\Debug\\VertexShader.cso", *this);
	auto layout = std::make_unique<InputLayout>(idc, *sh, *this);
	triangle.addBind(std::move(layout));

	triangle.addBind(std::move(sh));
	triangle.addBind(std::make_unique<Shader<ID3D11PixelShader>>("..\\x64\\Debug\\PixelShader.cso", *this));
	

	triangle.draw();
	pDeviceContext->DrawIndexed((UINT)indices.size(), 0, 0);

}
