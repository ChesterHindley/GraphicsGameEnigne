#include "Drawable.h"

Drawable::Drawable(Graphics& g) : VScbuf(g), GraphicsObject(g)
{
	//huh??
}

void Drawable::draw()
{
	for (auto& i : binds)
	{
		i->bind();
		
	}
	VScbuf.bind();
	// window draw? gfx draw?
	gfx.pDeviceContext->DrawIndexed(static_cast<UINT>(this->indicesCount()), 0, 0);
}

void Drawable::addBind(std::unique_ptr<Bindable>&& b)
{
	binds.emplace_back(std::move(b));

}

void Drawable::updateTransformation(const DirectX::XMFLOAT4X4& m)
{
	VScbuf.update(m);

}



