#pragma once
#include <vector>
#include "Graphics.h"
#include "GraphicsObject.h"
#include "Bindable.h"
#include <memory>
#include <DirectXMath.h>
#include "VSConstantBuffer.h"
//TODO expand this class ie transformation update etc
class Drawable : public GraphicsObject // since it can be drawn it should also have a constant buffer with position transformation
	// however if I am to update it I need to store it individually (or try dynamic cast on all binds)
	// 
{
	VSConstantBuffer VScbuf;
	std::vector<std::unique_ptr<Bindable>> binds;

protected:
	virtual ~Drawable() = default;


public:
	Drawable(Graphics&);
	void draw(); // should Bind() everything and call drawindexed
	void addBind(std::unique_ptr<Bindable>&&);
	void updateTransformation(const DirectX::XMFLOAT4X4&);
	virtual std::size_t indicesCount() const = 0;

	
};

