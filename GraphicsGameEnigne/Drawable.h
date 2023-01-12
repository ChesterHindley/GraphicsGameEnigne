#pragma once
#include "Graphics.h"
#include "GraphicsObject.h"
class Drawable : protected GraphicsObject
{

	Drawable(Graphics&);
	void Draw(); // should Bind() everything and call drawindexed
};

