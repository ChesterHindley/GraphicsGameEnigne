#pragma once
#include <wrl/client.h>
#include <d3d11.h>

class Window;

namespace wrl = Microsoft::WRL; // isn't this bad since it's a header that will be included in at least a few places
class Graphics
{
	friend class GraphicsObject; // no need to forward declare huh

	wrl::ComPtr<IDXGISwapChain> pSwapChain;
	wrl::ComPtr<ID3D11Device> pDevice;
	wrl::ComPtr<ID3D11DeviceContext> pDeviceContext;
	wrl::ComPtr<ID3D11RenderTargetView> pRenderTargetView;
	wrl::ComPtr<ID3D11DepthStencilView> pDepthStencilView;

public:
	Graphics(const Window &);
	HRESULT endFrame();
	void drawTriangle();
};
