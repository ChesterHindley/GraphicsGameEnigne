#pragma once
#include "Drawable.h"

class Triangle : public Drawable
{
	float xoffset,yoffset,zoffset;
	float rotx, roty, rotz;




	using Drawable::draw;
	
public:
	Triangle(float,float,float,float,float,float,Graphics& g);
	Triangle(const Triangle&) = default;

	void self_draw(float t);
	std::size_t indicesCount() const override;
	
};

