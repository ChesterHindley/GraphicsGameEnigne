#pragma once
#include <wrl/client.h>
#include <d3d11.h>

class Window;

class Graphics
{
	friend class GraphicsObject;

	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pDeviceContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDepthStencilView;

public:
	Graphics(const Window &);
	HRESULT endFrame();
	void drawTriangle();

};
