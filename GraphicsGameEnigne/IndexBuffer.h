#pragma once
#include <vector>
#include "Bindable.h"
class IndexBuffer : public Bindable
{
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
	std::size_t size;

public:
	IndexBuffer(std::vector<short int>& indices, Graphics&);
	auto getSize() const;
	void bind() override;
};

