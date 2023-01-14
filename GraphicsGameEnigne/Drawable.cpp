#include "Drawable.h"

Drawable::Drawable(Graphics& g) : GraphicsObject(g)
{

}

void Drawable::draw()
{
	for (auto& i : binds)
	{
		i->bind();
		
	}
	// window draw? gfx draw? 
}

void Drawable::addBind(std::unique_ptr<Bindable>&& b)
{
	binds.emplace_back(std::move(b));

}
