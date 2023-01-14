#pragma once
#include "Graphics.h"

class GraphicsObject
{
protected:
	struct{
	Microsoft::WRL::ComPtr<IDXGISwapChain>& pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Device>& pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>& pDeviceContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>& pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>& pDepthStencilView;
	}gfx;

	GraphicsObject(Graphics& g);
};

