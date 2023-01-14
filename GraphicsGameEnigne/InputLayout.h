#pragma once
#include <vector>
#include "Bindable.h"
#include "Shader.h"
class InputLayout : public Bindable
{

	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
public:
	InputLayout(const std::vector<D3D11_INPUT_ELEMENT_DESC>& desc, const Shader<ID3D11VertexShader>&, Graphics&);
	void bind() override;
};

