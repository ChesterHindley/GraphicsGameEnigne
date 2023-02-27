#include <vector>
#include <DirectXMath.h>
#include <filesystem>
#include <random>
#include "Graphics.h"
#include "Window.h"
#pragma comment(lib,"D3D11.lib")
#include "Triangle.h"
#include <array>


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
	
	Microsoft::WRL::ComPtr<ID3D11Resource> backBuffer;

	D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
		D3D11_CREATE_DEVICE_DEBUG, nullptr, 0, D3D11_SDK_VERSION, &scd,
		&pSwapChain, &pDevice, nullptr, &pDeviceContext);

	pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &backBuffer);
	pDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, &pRenderTargetView);


	D3D11_DEPTH_STENCIL_DESC depthStencilDesc{ .DepthEnable = true,.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL,.DepthFunc = D3D11_COMPARISON_LESS };
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilState;
	pDevice->CreateDepthStencilState(&depthStencilDesc, &depthStencilState);
	pDeviceContext->OMSetDepthStencilState(depthStencilState.Get(), 1);


	D3D11_TEXTURE2D_DESC dsd{ .Width = (UINT)w.getxSize(), .Height = (UINT)w.getySize(), .MipLevels = 1, .ArraySize = 1, .Format = DXGI_FORMAT_D16_UNORM, .SampleDesc{1,0},.Usage = D3D11_USAGE_DEFAULT, .BindFlags= D3D11_BIND_DEPTH_STENCIL };

	Microsoft::WRL::ComPtr<ID3D11Texture2D> pDepthTexture;
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
	static constexpr FLOAT color[4] = { 0,0,0,1 };
	auto res = pSwapChain->Present(1, 0);
	pDeviceContext->ClearDepthStencilView(pDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1, 0);
	pDeviceContext->ClearRenderTargetView(pRenderTargetView.Get(), color);
	return res;
}

void Graphics::drawTriangle() // Actually why put everything on heap
{


	//Triangle triangle(xydist(randengine), xydist(randengine), zdist(randengine), xydist(randengine), xydist(randengine), xydist(randengine), *this);
	static std::array<std::unique_ptr<Triangle>, 10> triangles;

	if (triangles[0] == nullptr)
	std::ranges::generate(triangles, [this] () {
	std::mt19937 randengine(std::random_device{}());
	std::uniform_real_distribution<float> xydist(-2, 2);
	std::uniform_real_distribution<float> zdist(2, 8);
	return std::make_unique<Triangle>(xydist(randengine), xydist(randengine), zdist(randengine), xydist(randengine), xydist(randengine), xydist(randengine), *this); });

	for (auto& i : triangles)
	{
		i.get()->self_draw(time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count());
	}
}

	//triangle.self_draw((time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count()));

