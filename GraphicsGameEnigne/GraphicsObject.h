#pragma once
class Graphics;
class GraphicsObject
{
protected:
	Graphics& gfx;
	GraphicsObject(Graphics& g) : gfx{ g }
	{}
};

