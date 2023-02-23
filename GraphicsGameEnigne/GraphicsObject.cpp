#include "GraphicsObject.h"

GraphicsObject::GraphicsObject(Graphics& g) :
	gfx{ 
	.pSwapChain{g.pSwapChain},
	.pDevice{g.pDevice},
	.pDeviceContext{g.pDeviceContext},
	.pRenderTargetView{g.pRenderTargetView},
	.pDepthStencilView{g.pDepthStencilView},
	.graphics{g}
	}
{}


