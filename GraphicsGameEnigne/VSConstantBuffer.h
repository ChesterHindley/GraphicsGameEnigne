#pragma once
#include "Bindable.h"
#include <DirectXMath.h>
class VSConstantBuffer : // class managing creation and access of constant buffer 
    // IT WILL NOT KNOW WHAT IS INSIDE THE MATRIX, IT NEEDS CONSISTENT AND COHERENT UPDATES FROM OUTSIDE CODE
    public Bindable
{
    Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer;

    struct { DirectX::XMFLOAT4X4 matrix; } data;
public:
    VSConstantBuffer(Graphics& g);

    void bind() override;

    void update(const DirectX::XMFLOAT4X4& m);


    

};

