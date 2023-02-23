#pragma once
#include "Drawable.h"

class Triangle : public Drawable
{
	using Drawable::draw;
	std::size_t idxCount;
public:
	Triangle(Graphics& g);
	void self_draw(float t);
	std::size_t indicesCount() const;
	
};

