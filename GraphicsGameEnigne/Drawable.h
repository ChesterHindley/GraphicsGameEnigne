#pragma once
#include <vector>
#include "Graphics.h"
#include "GraphicsObject.h"
#include "Bindable.h"
#include <memory>
#include <DirectXMath.h>
#include "VSConstantBuffer.h"
class Drawable : public GraphicsObject 
{
	VSConstantBuffer VScbuf;
	std::vector<std::unique_ptr<Bindable>> binds;

protected:
	virtual ~Drawable() = default;
	std::size_t idxCount;


public:
	Drawable(Graphics&);
	void draw(); // should Bind() everything and call drawindexed
	void addBind(std::unique_ptr<Bindable>&&);
	void updateTransformation(const DirectX::XMFLOAT4X4&);
	virtual std::size_t indicesCount() const = 0;

	
};

