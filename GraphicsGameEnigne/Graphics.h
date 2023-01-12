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

/*TODO
class GraphicsObject{};
class Graphics{};

class Bindable : GraphicsObject
{
    protected:
    Bindable(Graphics&){}
    virtual void Bind() = 0; // TODO CRPT LMAO

};
class comptr{};
template<class T>
class IndexBuffer :protected Bindable
{
    comptr p;
    std::vector<T> indices;
    IndexBuffer(Graphics& g, std::vector<T>&& idx) : Bindable(g), indices{idx}
    {
        //

    }

};
template<class Vertex>
class VertexBuffer :protected Bindable
{
    comptr p;
    std::vector<Vertex> vertices;
    VertexBuffer(Graphics& g, std::vector<Vertex>&& v) : Bindable(g), vertices{v}
    {
        //

    }

};


*/