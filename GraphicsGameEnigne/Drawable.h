#pragma once
#include <vector>
#include "Graphics.h"
#include "GraphicsObject.h"
#include "Bindable.h"
#include <memory>
class Drawable : protected GraphicsObject
{
	std::vector<std::unique_ptr<Bindable>> binds;
public:
	Drawable(Graphics&);
	void draw(); // should Bind() everything and call drawindexed
	void addBind(std::unique_ptr<Bindable>&&);
};

