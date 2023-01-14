#include "InputLayout.h"

InputLayout::InputLayout(const std::vector<D3D11_INPUT_ELEMENT_DESC>& desc,const Shader<ID3D11VertexShader>& shader ,Graphics& g) : Bindable(g)
{
	gfx.pDevice->CreateInputLayout(desc.data(), desc.size(), shader.data(), shader.getSize(), &pInputLayout);
}

void InputLayout::bind()
{
	gfx.pDeviceContext->IASetInputLayout(pInputLayout.Get());
}
